/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 23:21:36 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 13:12:47 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <float.h>
#include <stdint.h>

static void			convert_nan(t_pholder *pholder, long double num)
{
	unsigned char	bits[8];

	ft_memcpy((void *)bits, (void *)&num, 8);
	if (bits[0] & 0x80)
		pholder->converted_arg = ft_strcpy(ft_strnew(4), "-nan");
	else
		pholder->converted_arg = ft_strcpy(ft_strnew(5), "nan");
	
}

static void			convert_inf(t_pholder *pholder, long double num)
{
	if (num > 0)
		pholder->converted_arg = ft_strcpy(ft_strnew(4), "inf");
	else
		pholder->converted_arg = ft_strcpy(ft_strnew(5), "-inf");
}

void				convert_float(t_pholder *pholder)
{
	long double		num;

	num = get_long_double_num(pholder);
	if (ft_is_inf(num))
		convert_inf(pholder, num);
	else if (ft_is_nan(num))
		convert_nan(pholder, num);
	else if (pholder->arg_type->is_hex)
	{
		if (pholder->modifier && pholder->modifier->is_big_l)
			convert_long_double_hex(pholder);
		else
			convert_double_hex(pholder);
	}
	else if (pholder->arg_type->is_full_form)
		convert_float_full(num, pholder);
	else if (pholder->arg_type->is_exp_form)
		convert_float_exp(num, pholder);
	else if (pholder->arg_type->is_opt_form)
		convert_float_opt(num, pholder);
	apply_str_modifiers_float(pholder, num);
	if (pholder->is_uppercase)
		ft_capitalize(pholder->converted_arg);
	pholder->arg_len = ft_strlen(pholder->converted_arg);
}
