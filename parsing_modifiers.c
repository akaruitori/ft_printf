/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_modifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:43:05 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 14:10:35 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				add_flags(t_pholder **pholder, char **str)
{
	char			*current;
	t_flags			*flags;

	current = *str;
	flags = initialize_flags();
	while (ft_strchr(FLAGS, *current))
	{
		if (*current == '0')
			flags->zeroes = 1;
		else if (*current == ' ')
			flags->space = 1;
		else if (*current == '+')
			flags->plus = 1;
		else if (*current == '-')
			flags->left_align = 1;
		else if (*current == '#')
			flags->alt_form = 1;
		else if (*current == '\'')
			flags->apost = 1;
		current++;
	}
	*str = current;
	(*pholder)->flags = flags;
}

int					add_field_width(t_pholder **pholder, char **str,
									int numbered_args_flag)
{
	int				args_used;
	t_width			*width;
	char			*current;

	args_used = 0;
	current = *str;
	width = initialize_width();
	if (*current == '*')
	{
		if (numbered_args_flag)
			width->arg_pos = ft_strtol(current + 1, &current, 10);
		else
		{
			width->arg_pos = (*pholder)->arg_pos;
			(*pholder)->arg_pos++;
		}
		current++;
		width->is_from_arg = 1;
		args_used++;
	}
	else
		width->value = ft_strtol(current, &current, 10);
	*str = current;
	(*pholder)->width = width;
	return (args_used);
}

int					add_precision(t_pholder **pholder, char **str,
									int numbered_args_flag)
{
	int				args_used;
	t_precision		*precision;
	char			*current;

	args_used = 0;
	current = *str + 1;
	precision = initialize_precision();
	if (*current == '*')
	{
		if (numbered_args_flag)
			precision->arg_pos = ft_strtol(current + 1, &current, 10);
		else
		{
			precision->arg_pos = (*pholder)->arg_pos;
			(*pholder)->arg_pos++;
		}
		current++;
		precision->is_from_arg = 1;
		args_used++;
	}
	else
		precision->value = ft_strtol(current, &current, 10);
	*str = current;
	(*pholder)->precision = precision; //less than 0 check
	return (args_used);
}

void				add_length_modifier(t_pholder **pholder, char **str)
{
	t_modifier		*modifier;
	char			*current;

	current = *str;
	modifier = initialize_modifier();
	current += check_for_lh_modifiers(modifier, current);
	*str = current;
	(*pholder)->modifier = modifier;
}

int					parse(const char *format, t_pholder **pholders)
{
	unsigned int	numbered_args_flag;
	int				expected_args_num;
	char			*pholder_start;
	char			*format_temp;
	int				i;

	i = 0;
	format_temp = (char *)format;
	numbered_args_flag = (is_numbered_arg_used(format_temp) ? 1 : 0);
	expected_args_num = 0;
	while ((pholder_start = find_next_pholder(&format_temp))) // + 1?
	{
		if ((has_numbered_args(pholder_start) ^ numbered_args_flag))
			if (!(is_procent_pholder(pholder_start)))
			{
				free_pholders(pholders, i);
				return (-1);
			}
		expected_args_num += parse_a_pholder(pholder_start, &pholders[i],
									numbered_args_flag, expected_args_num + 1);
		pholders[i++]->pholder_len = format_temp - pholder_start;
	}
	return (expected_args_num);
}
