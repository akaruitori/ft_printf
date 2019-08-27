/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 03:21:11 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/21 17:52:11 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void						convert_pointer(t_pholder *pholder)
{
	unsigned long long int	ull_arg;
	char					*arg;

	ull_arg = (unsigned long long int)pholder->arg;
	// if (ull_arg == 0)
	// 	pholder->converted_arg = ft_strcpy(ft_strnew(6), "(nil)");
	// else
	// {
		arg = ft_ullint_to_str_base(ull_arg, 16);
		pholder->converted_arg = ft_strjoin("0x", arg);
		ft_strdel(&arg);
		pholder->arg_len = ft_strlen(pholder->converted_arg);
	// }
	if (pholder->width && ((size_t)pholder->width->value > pholder->arg_len))
	{
		if (pholder->flags && pholder->flags->left_align)
			apply_width_left_align(pholder, pholder->arg_len);
		else
			apply_width(pholder, pholder->arg_len);

	}
	pholder->arg_len = ft_strlen(pholder->converted_arg);
}
