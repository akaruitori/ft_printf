/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 02:39:08 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 15:37:47 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		apply_modifiers_string(t_pholder *pholder, int len)
{
	if (pholder->width && pholder->width->value > len)
	{
		if (pholder->flags && pholder->flags->left_align)
			apply_width_left_align(pholder, len);
		else
			apply_width(pholder, len);
	}
}

void		convert_string(t_pholder *pholder)
{
	char	*arg;
	int		arg_len;
	char	*temp;

	arg = (char *)pholder->arg;
	if (arg && *arg)
		temp = ft_strcpy(ft_strnew(ft_strlen(arg) + 1), arg);
	else if (arg && ((pholder->width && pholder->width->value > 7) ||
			(pholder->precision && pholder->precision->value < 7) ||
			(!pholder->width)))
		temp = ft_strnew(1);
	else
		temp = ft_strcpy(ft_strnew(7), "(null)");
	arg_len = ft_strlen(temp);
	if (pholder->precision && (pholder->precision->value >= 0) &&
		(pholder->precision->value < arg_len))
		arg_len = pholder->precision->value;
	if (!(pholder->converted_arg = ft_strnew(arg_len + 1)))
		malloc_error_exit();
	ft_strncpy(pholder->converted_arg, temp, arg_len);
	ft_strdel(&temp);
	apply_modifiers_string(pholder, arg_len);
	pholder->arg_len = ft_strlen(pholder->converted_arg);
}
