/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_convert_f_e_g.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:51:24 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 16:57:02 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char			*get_sign(long double num)
{
	unsigned char	bits[16];

	ft_memcpy((void *)bits, (void *)&num, 16);
	if (bits[9] & 0x80)
		return ("-");
	else
		return ("");
}

void				convert_float_full(long double num, t_pholder *pholder)
{
	char			*sign;
	char			*temp;
	int				precision;

	sign = get_sign(num);
	num = (num >= 0.l ? num : -num);
	precision = (pholder->precision && (pholder->precision->value >= 0) ?
					pholder->precision->value : 6);
	num += calculate_rounding(num, precision);
	if (num > (unsigned long long int)-1)
		convert_huge_float_full(num, pholder);
	else if ((int)num == 0)
		convert_small_float_full(num, pholder);
	else
		convert_medium_float_full(num, pholder);
	if (*sign)
	{
		temp = pholder->converted_arg;
		pholder->converted_arg = ft_strjoin(sign, pholder->converted_arg);
		ft_strdel(&temp);
	}
	if (pholder->arg_type->is_opt_form &&
		(!pholder->flags || (pholder->flags && !pholder->flags->alt_form)))
		del_trailing_point_zeroes(pholder->converted_arg);
}

void				convert_float_exp(long double num, t_pholder *pholder)
{
	int				exp;
	char			*exp_str;
	char			*sign;
	char			*temp;
	int				i;

	sign = (num >= 0. ? "\0" : "-");
	num = (num >= 0. ? num : -num);
	exp = get_float_exp(num);
	num /= ft_float_power(10.l, exp);
	convert_float_full(num, pholder);
	temp = ft_itoa(ft_abs(exp));
	if (!(exp_str = ft_strnew(4 + ft_strlen(temp))) || !temp)
		malloc_error_exit();
	ft_strcpy(exp_str, "e");
	i = 1;
	exp_str[i++] = (exp >= 0 ? '+' : '-');
	if (ft_abs(exp) < 10)
		exp_str[i++] = '0';
	ft_strcpy(exp_str + i, temp);
	ft_strdel(&temp);
	temp = pholder->converted_arg;
	pholder->converted_arg = ft_join_strings(3, sign, temp, exp_str);
	ft_strdel(&exp_str);
	ft_strdel(&temp);
}

static int			calculate_precision_opt_form(t_pholder *pholder)
{
	int				precision;

	if (pholder->precision)
	{
		if (pholder->precision->value >= 0)
			precision = pholder->precision->value;
		else
			precision = 1;
	}
	else
	{
		pholder->precision = initialize_precision();
		pholder->precision->value = 6;
		precision = 6;
	}
	return (precision);
}

void				convert_float_opt(long double num, t_pholder *pholder)
{
	int				precision;
	int				exp;

	precision = calculate_precision_opt_form(pholder);
	exp = get_float_exp(num >= 0.l ? num : -num);
	if (precision > exp && exp >= -4)
	{
		pholder->precision->value -= (1 + exp);
		convert_float_full(num, pholder);
	}
	else
	{
		pholder->precision->value--;
		convert_float_exp(num, pholder);
	}
}
