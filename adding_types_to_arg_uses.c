/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adding_types_to_arg_uses.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:52:51 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/27 15:53:21 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char				*get_sint_type(t_modifier *modifier)
{
	if (!modifier)
		return ("i");
	if (modifier->is_hh)
		return ("ich");
	if (modifier->is_h)
		return ("ishi");
	if (modifier->is_l)
		return ("ili");
	else
		return ("illi");
}

char				*get_uint_type(t_modifier *modifier)
{
	if (!modifier)
		return ("ui");
	if (modifier->is_hh)
		return ("uch");
	if (modifier->is_h)
		return ("ushi");
	if (modifier->is_l)
		return ("uli");
	else
		return ("ulli");
}

char				*get_type(t_pholder *pholder)
{
	t_arg_type		*arg_type;

	arg_type = pholder->arg_type;
	if (arg_type->is_unsigned_int)
		return (get_uint_type(pholder->modifier));
	if (arg_type->is_signed_int)
		return (get_sint_type(pholder->modifier));
	if (arg_type->is_float)
	{
		if (pholder->modifier && pholder->modifier->is_big_l)
			return ("dbll");
		return ("dbl");
	}
	if (arg_type->is_pointer || arg_type->is_char_str)
		return ("p");
	if (arg_type->is_char)
		return ("ich");
	else
		return ("i");
}