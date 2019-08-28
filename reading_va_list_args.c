/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_va_list_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:54:14 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 16:17:36 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		read_int_arg(va_list ap, char *type, int purpose,
								t_pholder *pholder)
{
	if (!type[1] || !ft_strcmp(type, "ich") || !ft_strcmp(type, "ishi"))
	{
		if (!type[1] && (purpose != NUM_ARG))
		{
			if (purpose == WIDTH_VALUE)
				read_width_value_from_arg(pholder, ap);
			else if (purpose == PRECISION_VALUE)
				read_precision_value_from_arg(pholder, ap);
		}
		else
		{
			pholder->arg = ft_malloc_or_exit(sizeof(int));
			*(int *)pholder->arg = va_arg(ap, int);
		}
	}
	else if (!ft_strcmp(type, "ili"))
	{
		pholder->arg = ft_malloc_or_exit(sizeof(long int));
		*(long int *)pholder->arg = va_arg(ap, long int);
	}
	else
	{
		pholder->arg = ft_malloc_or_exit(sizeof(long long int));
		*(long long int *)pholder->arg = va_arg(ap, long long int);
	}
}

static void		read_uint_arg(va_list ap, char *type, t_pholder *pholder)
{
	if (!ft_strcmp(type, "ui") || !ft_strcmp(type, "uch") ||
		!ft_strcmp(type, "ushi"))
	{
		pholder->arg = ft_malloc_or_exit(sizeof(unsigned int));
		*(unsigned int *)(pholder->arg) = va_arg(ap, unsigned int);
	}
	else if (!ft_strcmp(type, "uli"))
	{
		pholder->arg = ft_malloc_or_exit(sizeof(unsigned long int));
		*(unsigned long int *)(pholder->arg) = va_arg(ap, unsigned long int);
	}
	else
	{
		pholder->arg = ft_malloc_or_exit(sizeof(unsigned long long int));
		*(unsigned long long int *)(pholder->arg) = va_arg(ap,
													unsigned long long int);
	}
}

static void		read_double_arg(va_list ap, char *type, t_pholder *pholder)
{
	if (!ft_strcmp(type, "dbl"))
	{
		pholder->arg = ft_malloc_or_exit(sizeof(double));
		*(double *)pholder->arg = va_arg(ap, double);
	}
	else
	{
		pholder->arg = ft_malloc_or_exit(sizeof(long double));
		*(long double *)pholder->arg = va_arg(ap, long double);
	}
}

static void		read_pointer_arg(va_list ap, char *type, t_pholder *pholder)
{
	if (pholder->arg_type->is_char_str)
		pholder->arg = va_arg(ap, char *);
	else if (!ft_strcmp(type, "p"))
	{
		pholder->arg = va_arg(ap, void *);
	}
}

void			read_args(va_list ap, t_arg_use **arg_uses)
{
	int		i;
	char	*type;

	i = 1;
	while (arg_uses[i])
	{
		type = arg_uses[i]->type;
		if (*type == 'i')
			read_int_arg(ap, type, arg_uses[i]->purpose, arg_uses[i]->pholder);
		else if (*type == 'u')
			read_uint_arg(ap, type, arg_uses[i]->pholder);
		else if (*type == 'd')
			read_double_arg(ap, type, arg_uses[i]->pholder);
		else
			read_pointer_arg(ap, type, arg_uses[i]->pholder);
		if (arg_uses[i]->same_pos_next)
			save_args_for_all_pholders(arg_uses[i]);
		i++;
	}
}
