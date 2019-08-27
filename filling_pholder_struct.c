/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_pholder_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:45:30 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/27 15:46:32 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				add_arg_position(t_pholder **pholder, char **temp)
{
	(*pholder)->arg_pos = ft_strtol(*temp, temp, 10);
	*temp = *temp + 1;
}

void				add_int_type(t_pholder **pholder, char c)
{
	if (c == 'i' || c == 'd')
		(*pholder)->arg_type->is_signed_int = 1;
	else if (c == 'u' || c == 'b' || c == 'o' || c == 'x' || c == 'X')
	{
		(*pholder)->arg_type->is_unsigned_int = 1;
		if (c == 'b')
			(*pholder)->arg_type->is_binary = 1;
		else if (c == 'o')
			(*pholder)->arg_type->is_octal = 1;
		else if (c == 'x' || c == 'X')
		{
			(*pholder)->arg_type->is_hex = 1;
			if (c == 'X')
				(*pholder)->is_uppercase = 1;
		}
	}
	else if (c == 'p')
		(*pholder)->arg_type->is_pointer = 1;
	else if (c == 'k')
		(*pholder)->arg_type->is_time = 1;
}

void				add_float_type(t_pholder **pholder, char c)
{
	(*pholder)->arg_type->is_float = 1;
	if (c == 'f' || c == 'F')
		(*pholder)->arg_type->is_full_form = 1;
	else if (c == 'e' || c == 'E')
		(*pholder)->arg_type->is_exp_form = 1;
	else if (c == 'g' || c == 'G')
		(*pholder)->arg_type->is_opt_form = 1;
	else if (c == 'a' || c == 'A')
		(*pholder)->arg_type->is_hex = 1;
	if (c == 'F' || c == 'E' || c == 'G' || c == 'A')
		(*pholder)->is_uppercase = 1;
}

void				add_specifier(t_pholder **pholder, char **str)
{
	char			current;

	current = **str;
	if (ft_strchr("iduboxXpk", current))
		add_int_type(pholder, current);
	else if (ft_strchr("gGeEfFaA", current))
		add_float_type(pholder, current);
	else if (current == 'c')
		(*pholder)->arg_type->is_char = 1;
	else if (current == 's')
		(*pholder)->arg_type->is_char_str = 1;
}

int					add_procent(t_pholder **pholder)
{
	(*pholder)->is_procent = 1;
	(*pholder)->is_from_num_arg = 0;
	return (-1);
}
