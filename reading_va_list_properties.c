/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_va_list_properties.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:53:37 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 15:36:58 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	read_width_value_from_arg(t_pholder *pholder, va_list ap)
{
	pholder->width->arg = ft_malloc_or_exit(sizeof(int));
	*(int *)pholder->width->arg = va_arg(ap, int);
	pholder->width->value = *(int *)pholder->width->arg;
	if (pholder->width->value < 0)
	{
		if (!pholder->flags)
			pholder->flags = initialize_flags();
		pholder->flags->left_align = 1;
		pholder->width->value = -pholder->width->value;
	}
}

void	read_precision_value_from_arg(t_pholder *pholder,
													va_list ap)
{
	pholder->precision->arg = ft_malloc_or_exit(sizeof(int));
	*(int *)pholder->precision->arg = va_arg(ap, int);
	pholder->precision->value = *(int *)pholder->precision->arg;
}
