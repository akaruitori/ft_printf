/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_convert_parts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:46:52 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 15:18:34 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		del_trailing_point_zeroes(char *s)
{
	int		len;

	len = ft_strlen(s) - 1;
	while (s[len] && s[len] == '0')
	{
		s[len] = '\0';
		len--;
	}
	if (s[len] && s[len] == '.')
		s[len] = '\0';
}

static char	*convert_exp_to_str(t_float *fnum, int long_flag)
{
	char	*temp_exp;
	char	*result;
	int		exp_bias;
	int		normal_flag;

	exp_bias = get_exp_bias(long_flag);
	normal_flag = is_normal_float_num(fnum);
	if (fnum->exp)
		temp_exp = ft_itoa(ft_abs(fnum->exp - exp_bias));
	else if (normal_flag)
		temp_exp = ft_strcpy(ft_strnew(2), "0");
	else
		temp_exp = ft_itoa(ft_abs(fnum->exp - exp_bias + 1));
	if (!temp_exp)
		malloc_error_exit();
	result = ft_strjoin("p ", temp_exp);
	ft_strdel(&temp_exp);
	if ((fnum->exp >= exp_bias || !fnum->exp) && normal_flag)
		result[1] = '+';
	else
		result[1] = '-';
	return (result);
}

static char	*convert_man_to_str(t_float *fnum, int long_flag)
{
	char	*temp_man;
	char	*result;
	int		temp_man_len;
	int		expected_man_len;

	if (fnum->mantissa)
		temp_man = ft_ullint_to_str_base(fnum->mantissa, 16);
	else
		temp_man = ft_strnew(1);
	if (!temp_man)
		malloc_error_exit();
	temp_man_len = ft_strlen(temp_man);
	expected_man_len = (long_flag ? LDBL_MAN_LEN / 4 : DBL_MAN_LEN / 4);
	if ((temp_man_len < expected_man_len) && fnum->mantissa)
	{
		if (!(result = ft_strnew(expected_man_len + 1)))
			malloc_error_exit();
		ft_memset(result, '0', expected_man_len);
		ft_strcpy(result + expected_man_len - temp_man_len, temp_man);
		ft_strdel(&temp_man);
	}
	else
		result = temp_man;
	return (result);
}

void		convert_float_parts_to_hexstr(t_float *fnum,
			int long_flag, int precision_flag,
			unsigned char alt_form_flag)
{
	int		i;

	fnum->exp_str = convert_exp_to_str(fnum, long_flag);
	fnum->man_str = convert_man_to_str(fnum, long_flag);
	if (!is_zero(fnum))
		del_trailing_point_zeroes(fnum->man_str);
	fnum->prefix = ft_strnew(7);
	i = 0;
	if (fnum->sign)
		fnum->prefix[i++] = '-';
	ft_strcpy(fnum->prefix + i, "0x");
	i += 2;
	if (long_flag && is_normal_float_num(fnum))
	{
		fnum->prefix[i++] = fnum->man_str[0];
		ft_memmove(fnum->man_str, fnum->man_str + 1, ft_strlen(fnum->man_str));
	}
	else if (is_normal_float_num(fnum) && (!is_zero(fnum)))
		fnum->prefix[i++] = '1';
	else
		fnum->prefix[i++] = '0';
	if (precision_flag || fnum->man_str[0] || alt_form_flag)
		fnum->prefix[i] = '.';
}
