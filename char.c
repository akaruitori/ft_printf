/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 03:40:29 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 16:00:35 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			convert_char(t_pholder *pholder)
{
	char		arg;
	char		len;

	arg = *(char *)pholder->arg;
	if (arg == '\0')
		len = 0;
	else
		len = 1;
	pholder->converted_arg = ft_strnew(len);
	pholder->converted_arg[0] = arg;
	if (pholder->width && (pholder->width->value > len))
	{
		if (pholder->flags && pholder->flags->left_align)
			apply_width_left_align(pholder, 1);
		else
			apply_width(pholder, 1);
		pholder->arg_len = pholder->width->value;
	}
	else
		pholder->arg_len = 1;
}
