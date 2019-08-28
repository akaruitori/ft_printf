/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_hex_convert_rounding.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:49:31 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 16:08:07 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void					apply_precision_hex(t_float *fnum, int precision)
{
	char					*temp;
	int						man_len;

	man_len = ft_strlen(fnum->man_str);
	if (precision > man_len)
	{
		temp = fnum->man_str;
		if (!(fnum->man_str = ft_strnew(precision + 1)))
			malloc_error_exit();
		ft_strcpy(fnum->man_str, temp);
		ft_memset((void *)(fnum->man_str + man_len), '0', precision - man_len);
		ft_strdel(&temp);
	}
	else if (precision < man_len)
		ft_bzero((void *)(fnum->man_str + precision), man_len - precision);
}

static void					round_hex(t_float *fnum, int precision,
										int long_flag)
{
	int						man_len;
	unsigned long long int	man_temp;

	man_len = (long_flag ? LDBL_MAN_LEN / 4 : DBL_MAN_LEN / 4);
	man_temp = fnum->mantissa + 8.0 *
				ft_float_power(16, man_len - precision - 1);
	if (man_temp < fnum->mantissa)
	{
		fnum->exp += 4;
		fnum->mantissa = man_temp + ft_float_power(16, man_len - 1);
	}
	else if (!is_normal_float_num(fnum))
	{
		if (man_temp > ft_float_power(16, man_len - 1))
			fnum->exp++;
		fnum->mantissa = man_temp;
	}
	else
		fnum->mantissa = man_temp;
}

void						convert_long_double_hex(t_pholder *pholder)
{
	__uint128_t				num_bits;
	t_float					fnum;
	long double				num;
	char					*temp;
	unsigned char			alt_form_flag;

	num = *(long double *)pholder->arg;
	num_bits = *(__uint128_t *)&num;
	fnum.sign = (unsigned short)(num_bits >> (79) & 0x1);
	fnum.exp = (short int)((num_bits >> LDBL_MAN_LEN) & LDBL_EXP_MASK);
	fnum.mantissa = (unsigned long long)(num_bits & LDBL_MAN_MASK);
	alt_form_flag = ((pholder->flags && pholder->flags->alt_form) ? 1 : 0);
	if (pholder->precision && (pholder->precision->value >= 0))
	{
		round_hex(&fnum, pholder->precision->value, 1);
		convert_float_parts_to_hexstr(&fnum, 1, 1, alt_form_flag);
		apply_precision_hex(&fnum, pholder->precision->value);
	}
	else
		convert_float_parts_to_hexstr(&fnum, 1, 0, alt_form_flag);
	temp = ft_join_strings(3, fnum.prefix, fnum.man_str, fnum.exp_str);
	pholder->arg_len = ft_strlen(temp);
	pholder->converted_arg = temp;
	memfree_fnum(&fnum);
}

void						convert_double_hex(t_pholder *pholder)
{
	u_int64_t				num_bits;
	t_float					fnum;
	char					*temp;
	unsigned char			alt_form_flag;

	num_bits = *(u_int64_t *)pholder->arg;
	fnum.sign = (unsigned char)(num_bits >> (DBL_EXP_LEN + DBL_MAN_LEN));
	fnum.exp = (short int)((num_bits >> DBL_MAN_LEN) & DBL_EXP_MASK);
	fnum.mantissa = (unsigned long long)(num_bits & DBL_MAN_MASK);
	alt_form_flag = ((pholder->flags && pholder->flags->alt_form) ? 1 : 0);
	if ((pholder->precision && (pholder->precision->value >= 0)))
	{
		round_hex(&fnum, pholder->precision->value, 0);
		convert_float_parts_to_hexstr(&fnum, 0, 1, alt_form_flag);
		apply_precision_hex(&fnum, pholder->precision->value);
	}
	else
		convert_float_parts_to_hexstr(&fnum, 0, 0, alt_form_flag);
	temp = ft_join_strings(3, fnum.prefix, fnum.man_str, fnum.exp_str);
	pholder->arg_len = ft_strlen(temp);
	pholder->converted_arg = temp;
	memfree_fnum(&fnum);
}
