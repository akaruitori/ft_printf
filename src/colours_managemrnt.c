/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours_managemrnt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:11:50 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/24 01:54:12 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					any_colours_used(char *line, int line_len)
{
	char			*tag_st;
	char			*tag_end;

	if ((tag_st = ft_strnchr(line, '{', line_len)))
		if ((tag_end = ft_strnchr(tag_st, '}', line_len - (tag_st - line))))
			if (ft_strnstr(tag_end, "{eoc}", line_len - (tag_end - line)))
				return (1);
	return (0);
}

static char			*find_colour_tag(t_colour colours[COLOURS_NUM],
									int *c_num, char *line, int line_len)
{
	int				i;
	char			*tag_start;

	i = 0;
    tag_start = ft_strchr(line, '{');
	while (tag_start && i < COLOURS_NUM)
	{
		if (tag_start &&
            ft_strnequ(tag_start, colours[i].name, ft_strlen(colours[i].name)))
			if (ft_strnstr(tag_start, "{eoc}", line_len - (tag_start - line)))
			{
				*c_num = i;
				return (tag_start);
			}
		i++;
	}
	return (NULL);
}

static int			print_coloured_part(char *start, t_colour *colour, int len)
{
	int				coloured_part_len;

	colour->write_function();
	start += colour->tag_len;
	len -= colour->tag_len;
	coloured_part_len = ft_strnstr(start, "{eoc}", len) - start;
	write(1, start, coloured_part_len);
	switch_to_default();
	coloured_part_len += colour->tag_len + 5;
	return (coloured_part_len);
}

void				print_with_colours(char *line, int line_len)
{
	char			*temp;
	char			*tag_st;
	int				i;
	int				chars_printed;
	static t_colour	colours[COLOURS_NUM] = {{"{green}", 7, switch_to_green},
											{"{red}", 5, switch_to_red},
											{"{blue}", 6, switch_to_blue}};

	temp = line;
	while (any_colours_used(temp, line_len))
	{
		i = 0;
		chars_printed = 0;
		if (!(tag_st = find_colour_tag(colours, &i, temp, line_len)))
			break ;
		write(1, temp, tag_st - temp);
		chars_printed += tag_st - temp;
		chars_printed += print_coloured_part(tag_st, &colours[i], line_len);
		temp += chars_printed;
		line_len -= chars_printed;
	}
	write(1, temp, line_len);
}
