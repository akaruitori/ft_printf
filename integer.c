/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 19:00:47 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 15:30:27 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				apply_leading_zeroes_int(t_pholder *pholder,
											int width, int len)
{
	char			*temp;
	int				offset;

	temp = pholder->converted_arg;
	if (width >= len)
	{
		offset = width - len;
		if (temp[0] == '-')
			offset++;
		if (!(pholder->converted_arg = ft_strnew(width + 2)))
			malloc_error_exit();
		ft_memset(pholder->converted_arg, '0', offset);
		ft_strcpy(pholder->converted_arg + offset, temp);
		if (pholder->converted_arg[offset] == '-')
		{
			pholder->converted_arg[0] = '-';
			pholder->converted_arg[offset] = '0';
			pholder->converted_arg[offset + len] = '\0';
		}
		ft_strdel(&temp);
	}
	else if ((width == 0) && (len == 1) && (*temp == '0'))
		pholder->converted_arg[0] = '\0';
}

static void			apply_flags_int(t_pholder *pholder)
{
	if (pholder->flags->plus)
		apply_plus(&pholder->converted_arg);
	else if (pholder->flags->space)
		apply_space(&pholder->converted_arg);
	if (pholder->flags->apost)
		apply_apost(&pholder->converted_arg, ft_strlen(pholder->converted_arg));
}

static void			apply_str_modifiers_int(t_pholder *pholder)
{
	int				len;

	len = ft_strlen(pholder->converted_arg);
	if (pholder->precision && (pholder->precision->value >= 0))
		apply_leading_zeroes_int(pholder, pholder->precision->value, len);
	if (pholder->flags)
		apply_flags_int(pholder);
	len = ft_strlen(pholder->converted_arg);
	if (pholder->width && pholder->width->value > len)
	{
		if (pholder->flags && pholder->flags->left_align)
			apply_width_left_align(pholder, len);
		else
			apply_width(pholder, len);
		if (pholder->flags && pholder->flags->zeroes)
			if ((!pholder->precision ||
				(pholder->precision && pholder->precision->value < 0)) &&
				(!pholder->flags->left_align))
				apply_zeroes(pholder);
	}
}

void				convert_int(t_pholder *pholder)
{
	long long int	arg;

	if (!pholder->modifier)
		arg = (long long int)(*(int *)pholder->arg);
	else if (pholder->modifier->is_hh)
		arg = (long long int)(*(char *)pholder->arg);
	else if (pholder->modifier->is_h)
		arg = (long long int)(*(short int *)pholder->arg);
	else if (pholder->modifier->is_l)
		arg = (long long int)(*(long int *)pholder->arg);
	else
		arg = *(long long int *)pholder->arg;
	if (!(pholder->converted_arg = ft_llint_to_str_base(arg, 10)))
		malloc_error_exit();
	apply_str_modifiers_int(pholder);
	pholder->arg_len = ft_strlen(pholder->converted_arg);
}
