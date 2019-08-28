/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:13:29 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 14:18:20 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					is_correct_property_order(char **s, int num_arg_flag)
{
	if (**s && (**s == '*'))
	{
		(*s)++;
		if (num_arg_flag)
		{
			if (!is_correct_num_arg_order(s))
				return (0);
		}
		else if (ft_isdigit(**s))
			return (0);
	}
	while (**s && ft_isdigit(**s))
			(*s)++;
	return (1);
}

int					check_for_lh_modifiers(t_modifier *modifier, char *s)
{
	if (*s == 'L')
		modifier->is_big_l = 1;
	else if (*s == 'l')
	{
		if (*(s + 1) == 'l')
		{
			modifier->is_ll = 1;
			return (2);
		}
		else
			modifier->is_l = 1;
	}
	else if (*s == 'h')
	{
		if (*(s + 1) =='h')
		{
			modifier->is_hh = 1;
			return (2);
		}
		else
			modifier->is_h = 1;
	}
	return (1);
}

int					is_correct_length_modifier(char **s)
{
	if (**s && is_length_modifier(**s))
	{
		(*s)++;
		if (is_length_modifier(**s))
		{
			if (((*(*s - 1)) != **s) || (**s == 'L'))
				return (0);
			(*s)++;
		}
	}
	return (1);
}

int					is_correct_modifiers_order(char *s)
{
	int				num_arg_flag;

	num_arg_flag = is_num_arg_in_this_pholder(s);
	if (num_arg_flag)
		if (!is_correct_num_arg_order(&s))
			return (0);
	while (*s && is_flag(*s))
		s++;
	if (!is_correct_property_order(&s, num_arg_flag))
		return (0);
	if (*s && *s == '.')
	{
		s++;
		if (!is_correct_property_order(&s, num_arg_flag))
			return (0);
	}
	if (!is_correct_length_modifier(&s))
		return (0);
	if (!(*s && is_specifier(*s)))
		return (0);
	return (1);
}

int					is_valid_pholder(char *s)
{
	int				i;

	i = 1;
	if (s[i] && (s[i] == '%'))
		return (1);
	if (!is_correct_modifiers_order(s + i))
		return (0);
	while (s[i] && ((is_flag(s[i]) || ft_strchr(".*$", s[i]) ||
		ft_isdigit(s[i]) || is_length_modifier(s[i]) || is_specifier(s[i]))))
	{
		if (is_specifier(s[i]))
		{
			if (s[i] == '%')
			{
				if (is_valid_procent_pholder(s, i))
					return (i);
				else
					return (0);
			}
			else
				return(i);
		}
		i++;
	}
	return (0);
}
