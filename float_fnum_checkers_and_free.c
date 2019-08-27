/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_fnum_checkers_and_free.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:29:46 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/27 19:42:06 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int							is_zero(t_float *fnum)
{
	return (!fnum->exp && !fnum->mantissa);
}

int							is_normal_float_num(t_float *fnum)
{
	return (fnum->exp || !(fnum->mantissa));
}

void						memfree_fnum(t_float *fnum)
{
	ft_strdel(&(fnum->exp_str));
	ft_strdel(&(fnum->man_str));
	ft_strdel(&(fnum->prefix));
}
