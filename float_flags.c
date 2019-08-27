/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:56:08 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/27 19:57:01 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				apply_plus(char **s)
{
	char			*temp;

	temp = *s;
	if (ft_strchr(HEX_DIGITS, *temp) || ft_strequ(temp, "inf") ||
		ft_strequ(temp, "nan"))
	{
		*s = ft_strjoin("+", temp);
		ft_strdel(&temp);
	}
}

void				apply_space(char **s)
{
	char			*temp;

	temp = *s;
	if (ft_strchr(HEX_DIGITS, *temp) || ft_strequ(temp, "inf") ||
		ft_strequ(temp, "nan"))
	{
		if (*temp != '-')
		{
			*s = ft_strjoin(" ", temp);
			ft_strdel(&temp);
		}
	}
}

void				insert_commas(char **s, int start_pos, int sep_num, int len)
{
	char			*dest;
	char			*src;
	char			*temp;

	src = *s;
	temp = *s;
	*s = ft_strnew(len + sep_num + 1);
	ft_strncpy(*s, src, start_pos);
    src += start_pos;
	dest = *s + start_pos;
	while (sep_num--)
	{
		*dest++ = ',';
		ft_strncpy(dest, src, 3);
		dest += 3;
		src += 3;
	}
	ft_strcpy(dest, src);
	ft_strdel(&temp);
}

void				apply_apost(char **s, int len)
{
	int				sep_num;
	char			*temp;
	char			*start;

	sep_num = 0;
	temp = *s;
	while (*temp && !ft_strchr(HEX_DIGITS, *temp))
		temp++;
	if (*temp)
	{
		start = temp;
		while (*temp && ft_strchr(HEX_DIGITS, *temp))
			temp++;
		sep_num = (temp - start - 1) / 3;
		start += (temp - start - 1) % 3 + 1;
		insert_commas(s, start - *s, sep_num, len);
	}
}
