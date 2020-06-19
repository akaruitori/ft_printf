/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_uses_creation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:47:29 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 14:42:06 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_arg_use	*init_new_arg_use(void)
{
	t_arg_use		*new;

	new = (t_arg_use *)ft_malloc_or_exit(sizeof(t_arg_use));
	new->purpose = 0;
	new->type = "\0";
	new->pholder = NULL;
	new->same_pos_next = NULL;
	return (new);
}

static t_arg_use	**initialize_arg_uses(int arg_num)
{
	t_arg_use		**arg_uses;
	int				i;

	arg_uses = (t_arg_use **)ft_malloc_or_exit(sizeof(t_arg_use *) *
												(arg_num + 2));
	arg_uses[arg_num + 1] = NULL;
	i = 0;
	while (i <= arg_num)
	{
		arg_uses[i] = init_new_arg_use();
		i++;
	}
	return (arg_uses);
}

static void			fill_arg_use(t_arg_use *arg_use, t_pholder *pholder,
								int purpose, char *type)
{
	arg_use->purpose = purpose;
	arg_use->type = type;
	arg_use->pholder = pholder;
	arg_use->same_pos_next = NULL;
}

static void			add_arg_use(t_arg_use **arg_use, t_pholder *pholder,
								int purpose, char *type)
{
	t_arg_use		*new_arg_use;

	if (!((*arg_use)->pholder))
		fill_arg_use(*arg_use, pholder, purpose, type);
	else
	{
		new_arg_use = *arg_use;
		while (new_arg_use->same_pos_next)
			new_arg_use = new_arg_use->same_pos_next;
		new_arg_use->same_pos_next = init_new_arg_use();
		fill_arg_use(new_arg_use->same_pos_next, pholder, purpose, type);
	}
}

t_arg_use			**save_arg_uses(t_pholder **pholders, int arg_num)
{
	t_arg_use		**arg_uses;
	int				i;

	arg_uses = initialize_arg_uses(arg_num);
	i = 0;
	while (pholders[i])
	{
		if (!pholders[i]->is_procent)
			add_arg_use(&arg_uses[pholders[i]->arg_pos], pholders[i],
						NUM_ARG, get_type(pholders[i]));
		if (pholders[i]->width && pholders[i]->width->is_from_arg)
			add_arg_use(&arg_uses[pholders[i]->width->arg_pos], pholders[i],
						WIDTH_VALUE, "i");
		if (pholders[i]->precision && pholders[i]->precision->is_from_arg)
			add_arg_use(&arg_uses[pholders[i]->precision->arg_pos], pholders[i],
						PRECISION_VALUE, "i");
		i++;
	}
	return (arg_uses);
}
