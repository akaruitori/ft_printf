/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_arg_checkers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:30:51 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 14:08:50 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				is_correct_num_arg_order(char **s)
{
	if (**s && ft_isdigit(**s))
	{
		while (ft_isdigit(**s))
			(*s)++;
		if (**s != '$')
			return (0);
		(*s)++;
	}
	return (1);
}

int				is_num_arg_in_this_pholder(char *format) //
{

	while (*format && (*format != '%'))
	{
		if (*format == '$')
			return (1);
		format++;
	}
	return (0);
}

int				is_numbered_arg_used(const char *format)
{
	while ((*format && (*format != '%')) || (*(format + 1)
			&& (*(format + 1) == '%')))
	{
		format++;
		if ((*(format - 1) == '%') && *format == '%')
			format++;
	}
	if (*format)
		format++;
	while (*format && !is_specifier(*format))
	{
		if (*format == '$')
			return (1);
		format++;
	}
	return (0);
}

unsigned int	has_numbered_args(char *pholder_start)
{
	if (ft_isdigit(*pholder_start))
	{
		while (ft_isdigit(*pholder_start))
			pholder_start++;
		if (*pholder_start == '$')
			return (1);
	}
	return (0);
}
