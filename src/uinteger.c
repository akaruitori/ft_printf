/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uinteger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 03:34:33 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 15:40:59 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

short int					determine_base(t_pholder *pholder)
{
	if (pholder->arg_type->is_binary)
		return (2);
	if (pholder->arg_type->is_octal)
		return (8);
	if (pholder->arg_type->is_hex)
		return (16);
	return (10);
}

void						convert_uint(t_pholder *pholder)
{
	short int				base;
	unsigned long long int	arg;

	base = determine_base(pholder);
	if (!pholder->modifier)
		arg = (unsigned long long int)(*(unsigned int *)pholder->arg);
	else if (pholder->modifier->is_hh)
		arg = (unsigned long long int)(*(unsigned char *)pholder->arg);
	else if (pholder->modifier->is_h)
		arg = (unsigned long long int)(*(unsigned short int *)pholder->arg);
	else if (pholder->modifier->is_l)
		arg = (unsigned long long int)(*(unsigned long int *)pholder->arg);
	else
		arg = *(unsigned long long int *)pholder->arg;
	if (!(pholder->converted_arg = ft_ullint_to_str_base(arg, base)))
		malloc_error_exit();
	apply_str_modifiers_uint(pholder, base);
	if (pholder->is_uppercase)
		ft_capitalize(pholder->converted_arg);
	pholder->arg_len = ft_strlen(pholder->converted_arg);
}
