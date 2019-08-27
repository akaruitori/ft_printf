/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 16:15:44 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/08 23:01:49 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *str, char c, size_t n)
{
	char	*s;

	s = (char *)str;
	while (*s != c && *s != '\0' && --n)
		s++;
	if (*s == c)
		return (s);
	return (0);
}

/*
** Same as ft_strchr, but searches through first n bytes of string pointed
** by str.
*/
