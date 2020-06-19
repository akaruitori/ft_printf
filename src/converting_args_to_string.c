/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converting_args_to_string.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:58:38 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 13:19:42 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			convert_arg(t_pholder *pholder)
{
	if (pholder->arg_type->is_time)
		convert_time(pholder);
	if (pholder->arg_type->is_char)
		convert_char(pholder);
	if (pholder->arg_type->is_signed_int)
		convert_int(pholder);
	if (pholder->arg_type->is_unsigned_int)
		convert_uint(pholder);
	if (pholder->arg_type->is_float)
		convert_float(pholder);
	if (pholder->arg_type->is_char_str)
		convert_string(pholder);
	if (pholder->arg_type->is_pointer)
		convert_pointer(pholder);
	if (pholder->is_procent)
		convert_procent(pholder);
}

int					convert_args_to_strings(t_pholder **pholders)
{
	int				i;
	int				str_args_len;

	i = 0;
	str_args_len = 0;
	while (pholders[i])
	{
		convert_arg(pholders[i]);
		str_args_len += pholders[i]->arg_len;
		i++;
	}
	return (str_args_len);
}
