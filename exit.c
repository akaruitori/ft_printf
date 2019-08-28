/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:39:46 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 13:28:42 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				malloc_error_exit(void)
{
	write(1, "memory allocation error\n", 25);
	exit(EXIT_FAILURE);
}

void		*ft_malloc_or_exit(size_t size)
{
	void	*new_area;

	if (!(new_area = malloc(size)))
		malloc_error_exit();
	return (new_area);
}
