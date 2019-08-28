/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pholder_managment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:35:25 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 16:52:38 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					count_pholders(const char *format)
{
	int				pholders_num;
	char			*temp;
	int				pholder_len;

	temp = (char *)format;
	pholders_num = 0;
	while (*temp)
	{
		if (*temp == '%')
		{
			if ((pholder_len = is_valid_pholder(temp)))
			{
				temp += pholder_len;
				pholders_num++;
			}
		}
		temp++;
	}
	return (pholders_num);
}

char				*find_next_pholder(char **format)
{
	char			*start;
	char			*temp;
	int				diff;

	temp = *format;
	while (*temp && *temp != '%')
		temp++;
	if (*temp && !is_valid_pholder(temp))
	{
		diff = temp - *format + 1;
		*format += diff;
		return (find_next_pholder(format));
	}
	if (*temp && (*temp + 1))
		start = temp + 1;
	else
		return (NULL);
	temp++;
	while (*temp && !is_specifier(*temp))
		temp++;
	if (!(*temp))
		return (NULL);
	*format = ++temp;
	return (start);
}

static t_pholder	*initialize_pholder(int numbered_args_flag)
{
	t_pholder		*new_pholder;

	new_pholder = (t_pholder *)malloc(sizeof(t_pholder));
	if (!new_pholder)
		malloc_error_exit();
	new_pholder->is_from_num_arg = (numbered_args_flag ? 1 : 0);
	new_pholder->flags = NULL;
	new_pholder->width = NULL;
	new_pholder->precision = NULL;
	new_pholder->modifier = NULL;
	new_pholder->is_uppercase = 0;
	new_pholder->is_procent = 0;
	new_pholder->arg_type = initialize_arg_type();
	new_pholder->is_procent = 0;
	new_pholder->pholder_len = 0;
	new_pholder->converted_arg = NULL;
	return (new_pholder);
}

int					parse_a_pholder(char *start, t_pholder **pholder,
									int numbered_args_flag, int pholder_num)
{
	int				args_used;
	char			*temp;

	args_used = 1;
	temp = start;
	*pholder = initialize_pholder(numbered_args_flag);
	if (numbered_args_flag)
		add_arg_position(pholder, &temp);
	else
		(*pholder)->arg_pos = pholder_num;
	if (*temp && is_flag(*temp))
		add_flags(pholder, &temp);
	if (*temp && (ft_isdigit(*temp) || *temp == '*'))
		args_used += add_field_width(pholder, &temp, numbered_args_flag);
	if (*temp && (*temp == '.'))
		args_used += add_precision(pholder, &temp, numbered_args_flag);
	if (*temp && is_length_modifier(*temp))
		add_length_modifier(pholder, &temp);
	if (*temp == '%')
		args_used += add_procent(pholder);
	else
		add_specifier(pholder, &temp);
	return (args_used);
}
