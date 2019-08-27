/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_output_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:00:19 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/27 16:06:14 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					count_pholders_len(t_pholder **pholders)
{
	int				i;
	int				len;

	i = 0;
	len = 0;
	while (pholders[i])
	{
		len += pholders[i]->pholder_len + 1;
		i++;
	}
	return (len);
}

void				create_line(t_pholder **pholders, const char *format,
								int line_len, char **line)
{
	int				i;
	char			*temp_format;
	char			*format_start;
	char			*pholder_start;
	int				copied_len;

	*line = ft_strnew(line_len + 1);
	temp_format = (char *)format;
	format_start = (char *)format;
	copied_len = 0;
	i = 0;
	while (pholders[i])
	{
		pholder_start = find_next_pholder(&temp_format) - 1;
		ft_strncpy(*line + copied_len, format_start,
					pholder_start - format_start);
		copied_len += pholder_start - format_start;
		ft_strncpy(*line + copied_len, pholders[i]->converted_arg,
					pholders[i]->arg_len);
		copied_len += pholders[i]->arg_len;
		format_start = temp_format;
		i++;
	}
	if (*format_start)
		ft_strncpy(*line + copied_len, format_start, ft_strlen(format_start));
}


int					create_output_string(char **line, t_pholder **pholders,
										va_list ap, const char *format)
{
	void			**args;
	int				expected_args_num;
	int				dub_num;
	int				line_len;

	if ((expected_args_num = parse(format, pholders)) < 0)
		return (0);
	if ((dub_num = check_and_count_dub_args(pholders, expected_args_num)) > 0)
		expected_args_num -= dub_num;
	if (dub_num < 0)
		return (0);
	if (!(args = save_args(ap, pholders, expected_args_num)))
		return (0);
	line_len = convert_args_to_strings(pholders);
	line_len = line_len + ft_strlen(format) - count_pholders_len(pholders);
	create_line(pholders, format, line_len, line);
	if (args[0])
		free_args(args);
	ft_memdel((void **)&args);
	return (line_len);
}

int					handle_formatted_input(va_list ap, const char *format,
											int pholders_num, char **line)
{
	t_pholder		**pholders;
	int				line_len;

	pholders = (t_pholder **)malloc(sizeof(t_pholder *) * (pholders_num + 1));
	if (!(pholders))
		exit(EXIT_FAILURE);
	pholders[pholders_num] = NULL;
	if (!(line_len = create_output_string(line, pholders, ap, format)))
		return (0);
	free_pholders(pholders, pholders_num);
	ft_memdel((void **)&pholders);
	return (line_len);
}