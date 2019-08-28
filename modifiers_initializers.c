/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers_initializers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:40:26 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 15:31:08 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_arg_type		*initialize_arg_type(void)
{
	t_arg_type	*new_arg_type;

	new_arg_type = (t_arg_type *)ft_malloc_or_exit(sizeof(t_arg_type));
	ft_bzero(new_arg_type, sizeof(t_arg_type));
	return (new_arg_type);
}

t_flags			*initialize_flags(void)
{
	t_flags		*new_flags;

	new_flags = (t_flags *)ft_malloc_or_exit(sizeof(t_flags));
	new_flags->space = 0;
	new_flags->plus = 0;
	new_flags->left_align = 0;
	new_flags->apost = 0;
	new_flags->alt_form = 0;
	new_flags->zeroes = 0;
	return (new_flags);
}

t_width			*initialize_width(void)
{
	t_width		*new_width;

	new_width = (t_width *)ft_malloc_or_exit(sizeof(t_width));

 	new_width->value = 0;
	new_width->is_from_arg = 0;
	new_width->arg_pos = 0;
	return (new_width);
}

t_precision		*initialize_precision(void)
{
	t_precision	*precision;

	precision = (t_precision *)ft_malloc_or_exit(sizeof(t_precision));
	precision->value = 0;
	precision->is_from_arg = 0;
	precision->arg_pos = 0;
	return (precision);
}

t_modifier		*initialize_modifier(void)
{
	t_modifier	*new_modifier;

	new_modifier = (t_modifier *)ft_malloc_or_exit(sizeof(t_modifier));
	new_modifier->is_big_l = 0;
	new_modifier->is_l = 0;
	new_modifier->is_ll = 0;
	new_modifier->is_h = 0;
	new_modifier->is_hh = 0;
	return (new_modifier);
}
