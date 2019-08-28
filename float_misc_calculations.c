/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_misc_calculations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:42:28 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 14:05:15 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double		calculate_rounding(long double num, int precision)
{
	long double	addition;
	long double	exp;
	long double	exp_num;

	if (precision > LDBL_DIG)
		precision = LDBL_DIG;
	exp = ft_float_power(10.l, precision);
	addition = 0.5 / exp;
	exp_num = num * exp * 10.l;
	if (((exp_num - (int)exp_num)) == 0.l && ((int)exp_num % 10 == 5))
		if (((int)(num * exp) % 2) == 1)
			return ( 1.l / exp);
	return (addition);
}

short int		get_exp_bias(int long_flag)
{
	return (long_flag ? LDBL_EXP_BIAS : DBL_EXP_BIAS);
}

int				get_float_order(long double num)
{
	int			order;

	order = 1;
	while (num > 10.l)
	{
		order++;
		num /= 10.l;
	}
	return (order);
}

long double		get_long_double_num(t_pholder *pholder)
{
	if (pholder->modifier && pholder->modifier->is_big_l)
		return (*(long double *)pholder->arg);
	return ((long double)*(double *)pholder->arg);
}

int				get_float_exp(long double num)
{
	int			result;

	result = 0;
	while ((long long int)num >= 10)
	{
		num /= 10.l;
		result++;
	}
	while (num != 0.l && (long long int)num == 0)
	{
		num *= 10.l;
		result--;
	}
	return (result);
}
