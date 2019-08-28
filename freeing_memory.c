/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:06:23 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 16:52:18 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			free_arg_uses(t_arg_use **arg_uses)
{
	int			i;
	t_arg_use	*temp;
	t_arg_use	*temp_to_free;

	i = 1;
	ft_memdel((void **)&arg_uses[0]);
	while (arg_uses[i])
	{
		temp = arg_uses[i]->same_pos_next;
		while (temp)
		{
			temp_to_free = temp;
			temp = temp->same_pos_next;
			ft_memdel((void **)&temp_to_free);
		}
		ft_memdel((void **)&arg_uses[i]);
		i++;
	}
}

void			free_args(void **args)
{
	int			i;

	i = 0;
	while (args[i])
	{
		ft_memdel(&args[i]);
		i++;
	}
}

void			free_pholders(t_pholder **pholders, int pholders_num)
{
	int			i;

	i = 0;
	while (i < pholders_num)
	{
		if (pholders[i]->flags)
			ft_memdel((void **)&(pholders[i]->flags));
		if (pholders[i]->width)
			ft_memdel((void **)&(pholders[i]->width));
		if (pholders[i]->precision)
			ft_memdel((void **)&(pholders[i]->precision));
		if (pholders[i]->modifier)
			ft_memdel((void **)&(pholders[i]->modifier));
		if (pholders[i]->arg_type)
			ft_memdel((void **)&(pholders[i]->arg_type));
		if (pholders[i]->converted_arg)
			ft_strdel(&(pholders[i]->converted_arg));
		ft_memdel((void **)&(pholders[i]));
		i++;
	}
}
