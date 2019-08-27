/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:10:36 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/27 16:14:39 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_line(char *line, int line_len)
{
	if (any_colours_used(line, line_len))
		print_with_colours(line, line_len);
	else
		write(1, line, line_len);
	ft_strdel(&line);
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	int		pholders_num;
	char	*line;
	int		line_len;

	if (!format)
		return (-1);
	pholders_num = count_pholders(format);
	if (pholders_num > 0)
	{
		va_start(ap, format);
		line_len = handle_formatted_input(ap, format, pholders_num, &line);
		va_end(ap);
	}
	else
	{
		line_len = ft_strlen(format);
		if (line_len > 0)
			line = ft_strcpy(ft_strnew(line_len + 1), (char *)format);
	}
	if (line_len > 0)
		print_line(line, line_len);
	return (line_len);
}
