/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 03:43:47 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/21 17:52:33 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			convert_procent(t_pholder *pholder)
{
	pholder->converted_arg = ft_strnew(2);
	pholder->converted_arg[0] = '%';
	if (pholder->width && pholder->width->value > 1)
	{
		if (pholder->flags && pholder->flags->left_align)
			apply_width_left_align(pholder, 1);
		else
		{
			apply_width(pholder, 1);
			if (pholder->flags && pholder->flags->zeroes)
				apply_zeroes(pholder);
		}
		pholder->arg_len = ft_strlen(pholder->converted_arg);
	}
	else
		pholder->arg_len = 1;
}
