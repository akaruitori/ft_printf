/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint_modifiers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:58:47 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 16:54:30 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char				*get_alt_form_prefix(int base)
{
	char			*prefix;

	if (base == 2)
		prefix = ft_strcpy(ft_strnew(3), "0b");
	else if (base == 8)
		prefix = ft_strcpy(ft_strnew(2), "0");
	else
		prefix = ft_strcpy(ft_strnew(3), "0x");
	return (prefix);
}

void				apply_alt_form_uint(char **s, int base)
{
	char			*prefix;
	char			*temp;
	int				offset;

	if (base == 2 || base == 8 || base == 16)
	{
		prefix = get_alt_form_prefix(base);
		temp = *s;
		if (*temp && *temp == ' ' && *(temp + 1) && *(temp + 1) == ' ')
		{
			offset = -ft_strlen(prefix);
			while (*temp++ == ' ')
				offset++;
			ft_strncpy(*s + offset, prefix, ft_strlen(prefix));
		}
		else if (*temp)
		{
			if (*temp == ' ' && *(temp + 1))
				ft_memmove(*s, *s + 1, ft_strlen(*s) + 1);
			*s = ft_strjoin(prefix, temp);
			ft_strdel(&temp);
		}
		ft_strdel(&prefix);
	}
}

void				apply_flags_uint(t_pholder *pholder, int base)
{
	unsigned int	arg;

	arg = *(unsigned int *)pholder->arg;
	if (pholder->flags->apost)
		apply_apost(&pholder->converted_arg, ft_strlen(pholder->converted_arg));
	if (pholder->flags->alt_form)
	{
		if (arg)
			if (!(*pholder->converted_arg == '0' &&
					pholder->arg_type->is_octal))
				apply_alt_form_uint(&pholder->converted_arg, base);
		if (!pholder->converted_arg[0] && pholder->arg_type->is_octal)
			pholder->converted_arg = ft_strcpy(ft_strnew(2), "0");
	}
}

void				apply_zeroes_uint(t_pholder *pholder, int width, int len)
{
	char			*temp;
	int				offset;
	int				base;
	char			*prefix;
	int				prefix_len;

	temp = pholder->converted_arg;
	base = determine_base(pholder);
	if (width > len)
	{
		offset = width - len;
		if ((base != 10) && pholder->flags && pholder->flags->alt_form &&
			*(unsigned int *)pholder->arg)
			prefix = get_alt_form_prefix(base);
		else
			prefix = ft_strnew(1);
		prefix_len = ft_strlen(prefix);
		if (!(pholder->converted_arg = ft_strnew(width + 1)))
			malloc_error_exit();
		ft_strcpy(pholder->converted_arg + offset, temp);
		ft_memset(pholder->converted_arg, '0', offset + prefix_len);
		ft_strncpy(pholder->converted_arg, prefix, prefix_len);
		ft_strdel(&prefix);
		ft_strdel(&temp);
	}
}

void				apply_str_modifiers_uint(t_pholder *pholder, int base)
{
	int				len;

	len = ft_strlen(pholder->converted_arg);
	if (pholder->precision)
		apply_leading_zeroes_int(pholder, pholder->precision->value, len);
	if (pholder->flags)
		apply_flags_uint(pholder, base);
	len = ft_strlen(pholder->converted_arg);
	if (pholder->width && pholder->width->value > len)
	{
		if (pholder->flags && pholder->flags->left_align)
			apply_width_left_align(pholder, len);
		else if (pholder->flags && pholder->flags->zeroes && !pholder->precision
				&& (!pholder->flags || !pholder->flags->left_align))
			apply_zeroes_uint(pholder, pholder->width->value, len);
		else
			apply_width(pholder, len);
	}
}
