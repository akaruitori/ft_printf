/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier_checkers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:11:34 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/27 15:13:03 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					is_specifier(char c)
{
	if (ft_strchr(SPECIFIERS, (int)c) != NULL)
		return (1);
	return (0);
}

int					is_flag(char c)
{
	return (ft_strchr(FLAGS, c) != NULL);
}

int					is_length_modifier(char c)
{
	return (ft_strchr(LENGTH_MODIFIERS, c) != NULL);
}
