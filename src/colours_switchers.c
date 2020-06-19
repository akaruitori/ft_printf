/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours_switchers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:10:31 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/27 16:11:13 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				switch_to_green(void)
{
	write(1, "\033[0;32m", 7);
}

void				switch_to_red(void)
{
	write(1, "\033[0;31m", 7);
}

void				switch_to_blue(void)
{
	write(1, "\033[0;34m", 7);
}

void				switch_to_default(void)
{
	write(1, "\033[0m", 4);
}
