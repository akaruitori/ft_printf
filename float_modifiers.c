/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_modifiers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:57:12 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/27 19:58:12 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				apply_width_left_align(t_pholder *pholder, int len)
{
	int				fill_len;
	char			*temp;

	fill_len = pholder->width->value - len;
	temp = pholder->converted_arg;
	pholder->converted_arg = ft_strnew(pholder->width->value + 1);
	ft_memset(pholder->converted_arg, ' ', pholder->width->value);
	ft_strncpy(pholder->converted_arg, temp, len);
	ft_strdel(&temp);
}

void				apply_width(t_pholder *pholder, int len)
{
	int				fil_len;
	char			*temp;

	fil_len = pholder->width->value - len;
	temp = pholder->converted_arg;
	pholder->converted_arg = ft_strnew(fil_len + len + 1);
	ft_memset(pholder->converted_arg, ' ', fil_len);
	ft_strcpy(pholder->converted_arg + fil_len, temp);
	ft_strdel(&temp);
}


void				apply_zeroes(t_pholder *pholder)
{
	char			*temp;

	temp = pholder->converted_arg;
	while (*temp == ' ')
	{
		*temp = '0';
		temp++;
	}
	if ((*temp == '+' || *temp == '-') && temp != pholder->converted_arg)
	{
		if (*temp == '+')
			*pholder->converted_arg = '+';
		else
			*pholder->converted_arg = '-';
		*temp = '0';
	}
	else if (pholder->flags->space && (*pholder->converted_arg != '-'))
		*pholder->converted_arg = ' ';
}

void				apply_str_modifiers_float(t_pholder *pholder,
											long double num)
{
	int				len;
	unsigned char	inf_flag;
	unsigned char	nan_flag;

	inf_flag = ft_is_inf(num);
	nan_flag = ft_is_nan(num);
	len = ft_strlen(pholder->converted_arg);
	if (pholder->flags && !nan_flag)
	{
		if (pholder->flags->apost)
			apply_apost(&pholder->converted_arg, len);
		if (pholder->flags->plus)
			apply_plus(&(pholder->converted_arg));
		else if (pholder->flags->space)
			apply_space(&pholder->converted_arg);
	}
	len = ft_strlen(pholder->converted_arg);
	if (pholder->width && (pholder->width->value > len))
	{
		if (pholder->flags && pholder->flags->left_align)
			apply_width_left_align(pholder, len);
		else
			apply_width(pholder, len);
		if (pholder->flags && pholder->flags->zeroes && !inf_flag && !nan_flag)
			apply_zeroes(pholder);
	}
}