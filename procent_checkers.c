/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procent_checkers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:18:50 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/27 15:30:40 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					is_valid_procent_pholder(char *s, int pholder_len)
{
	if (pholder_len == 1)
		return (1);
	while(--pholder_len >= 1)
	{
		if (!ft_strchr(FLAGS, s[pholder_len]) && !ft_isdigit(s[pholder_len]) &&
			(s[pholder_len] != '.'))
			return (0);
	}
	return (1);
}

int					is_procent_pholder(char	*start)
{
	while (!is_specifier(*start))
		start++;
	if (*start == '%')
		return (1);
	return (0);
}