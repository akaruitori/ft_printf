/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 03:21:11 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 15:33:56 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void						convert_pointer(t_pholder *pholder)
{
	unsigned long long int	ull_arg;
	char					*arg;

	ull_arg = (unsigned long long int)pholder->arg;
	if (!(arg = ft_ullint_to_str_base(ull_arg, 16)))
		malloc_error_exit();
	pholder->converted_arg = ft_strjoin("0x", arg);
	ft_strdel(&arg);
	pholder->arg_len = ft_strlen(pholder->converted_arg);
	if (pholder->width && ((size_t)pholder->width->value > pholder->arg_len))
	{
		if (pholder->flags && pholder->flags->left_align)
			apply_width_left_align(pholder, pholder->arg_len);
		else
			apply_width(pholder, pholder->arg_len);

	}
	pholder->arg_len = ft_strlen(pholder->converted_arg);
}
