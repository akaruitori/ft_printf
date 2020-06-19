/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_uses_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:49:12 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 16:02:51 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		is_valid_uses(t_arg_use **arg_uses)
{
	char		*temp_type;
	t_arg_use	*temp_arg_use;
	int			i;

	i = 1;
	while (arg_uses[i])
	{
		temp_type = arg_uses[i]->type;
		temp_arg_use = arg_uses[i]->same_pos_next;
		while (temp_arg_use)
		{
			if (ft_strcmp(temp_type, temp_arg_use->type))
				return (0);
			temp_arg_use = temp_arg_use->same_pos_next;
		}
		i++;
	}
	return (1);
}

static void		*get_arg_address(t_arg_use *arg_use)
{
	if (arg_use->purpose == NUM_ARG)
		return (arg_use->pholder->arg);
	else
	{
		if (arg_use->purpose == WIDTH_VALUE)
			return (arg_use->pholder->width->arg);
		else
			return (arg_use->pholder->precision->arg);
	}
}

void			save_args_for_all_pholders(t_arg_use *arg_use)
{
	t_arg_use	*temp_arg_use;
	void		*arg;

	arg = get_arg_address(arg_use);
	temp_arg_use = arg_use->same_pos_next;
	while (temp_arg_use)
	{
		if (temp_arg_use->purpose == NUM_ARG)
		{
			temp_arg_use->pholder->arg = arg;
		}
		else if (temp_arg_use->purpose == WIDTH_VALUE)
			temp_arg_use->pholder->width->value = *(int *)arg;
		else if (temp_arg_use->purpose == PRECISION_VALUE)
			temp_arg_use->pholder->precision->value = *(int *)arg;
		temp_arg_use = temp_arg_use->same_pos_next;
	}
}

static void		**get_unique_args(t_arg_use **arg_uses, int args_num)
{
	void		**args;
	int			aui;
	int			ai;

	args = (void **)ft_malloc_or_exit(sizeof(void *) * (args_num + 1));
	args[args_num] = NULL;
	aui = 0;
	ai = 0;
	while (arg_uses[++aui])
	{
		if (*arg_uses[aui]->type == 'p' ||
			(*arg_uses[aui]).pholder->is_procent == 1)
			continue;
		if (arg_uses[aui]->purpose == NUM_ARG)
			args[ai] = arg_uses[aui]->pholder->arg;
		else if (arg_uses[aui]->purpose == WIDTH_VALUE)
			args[ai] = arg_uses[aui]->pholder->width->arg;
		else
			args[ai] = arg_uses[aui]->pholder->precision->arg;
		ai++;
	}
	while (ai < args_num)
		args[ai++] = NULL;
	return (args);
}

void			**save_args(va_list ap, t_pholder **pholders, int args_num)
{
	t_arg_use	**arg_uses;
	void		**args;

	arg_uses = save_arg_uses(pholders, args_num);
	if (!is_valid_uses(arg_uses))
		return (NULL);
	read_args(ap, arg_uses);
	args = get_unique_args(arg_uses, args_num);
	free_arg_uses(arg_uses);
	ft_memdel((void **)&arg_uses);
	return (args);
}
