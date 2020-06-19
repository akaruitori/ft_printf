/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_args_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:46:48 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 15:32:18 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	*save_args_quantity(t_pholder **pholders, int args_num)
{
	int		i;
	int		*each_arg_amount;

	if (!(each_arg_amount = (int *)ft_memalloc(sizeof(int) * (args_num + 2))))
		malloc_error_exit();
	ft_memset(each_arg_amount, 0, args_num + 2);
	i = 0;
	while (pholders[i])
	{
		if (!pholders[i]->is_procent)
			each_arg_amount[pholders[i]->arg_pos]++;
		if (pholders[i]->width && pholders[i]->width->is_from_arg)
			each_arg_amount[pholders[i]->width->arg_pos]++;
		if (pholders[i]->precision && pholders[i]->precision->is_from_arg)
			each_arg_amount[pholders[i]->precision->arg_pos]++;
		i++;
	}
	return (each_arg_amount);
}

int			check_and_count_dub_args(t_pholder **pholders,
											int expected_args_num)
{
	int		*each_arg_amount;
	int		i;
	int		sum;
	int		dublicates;

	each_arg_amount = save_args_quantity(pholders, expected_args_num);
	i = 1;
	sum = 0;
	dublicates = 0;
	while (each_arg_amount[i] > 0)
	{
		sum += each_arg_amount[i];
		dublicates += (each_arg_amount[i] > 1 ? (each_arg_amount[i] - 1) : 0);
		i++;
	}
	ft_memdel((void **)&each_arg_amount);
	return (sum < expected_args_num ? -1 : dublicates);
}
