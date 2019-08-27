/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_additional_move_to_libft_02.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:27:07 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/27 19:29:08 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_is_inf(long double num)
{
	return ((num == 1.l / 0.l) || (num == -1.l / 0.l));
}

int					ft_is_nan(long double num)
{
	return (num != num);
}

void				ft_capitalize(char *s)
{
	while (*s)
	{
		if (ft_isalpha(*s))
			*s = ft_toupper(*s);
		s++;
	}
}