/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uinteger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 03:34:33 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/21 20:16:29 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// void		apply_apost(char **s, int len);
// void		apply_space(char **s);
// void		apply_plus(char **s);
// void		apply_width(t_pholder *pholder, int len);
// void		apply_width_left_align(t_pholder *pholder, int len);
// void		apply_zeroes(t_pholder *pholder);
// void		apply_leading_zeroes_int(t_pholder *pholder, int width, int len);
// void		ft_capitalize(char *s);

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
			offset = - ft_strlen(prefix);
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
	// char			*temp;
	unsigned int	arg;

	arg = *(unsigned int *)pholder->arg;
	if (pholder->flags->apost)
		apply_apost(&pholder->converted_arg, ft_strlen(pholder->converted_arg));
	if (pholder->flags->alt_form)
	{
		if (arg)
			if (!(*pholder->converted_arg == '0' && pholder->arg_type->is_octal))
				apply_alt_form_uint(&pholder->converted_arg, base);
		if (!pholder->converted_arg[0] && pholder->arg_type->is_octal)
		{
			// leak?
			pholder->converted_arg = ft_strcpy(ft_strnew(2), "0");
		}
	}
}

short int		determine_base(t_pholder *pholder)
{
	if (pholder->arg_type->is_binary)
		return (2);
	if (pholder->arg_type->is_octal)
		return (8);
	if (pholder->arg_type->is_hex)
		return (16);
	return (10);
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
		pholder->converted_arg = ft_strnew(width + 1);
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


void						convert_uint(t_pholder *pholder)
{
	short int				base;
	unsigned long long int	arg;

	base = determine_base(pholder);
	if (!pholder->modifier)
		arg = (unsigned long long int)(*(unsigned int *)pholder->arg);
	else if (pholder->modifier->is_hh)
		arg = (unsigned long long int)(*(unsigned char *)pholder->arg);
	else if (pholder->modifier->is_h)
		arg = (unsigned long long int)(*(unsigned short int *)pholder->arg);
	else if (pholder->modifier->is_l)
		arg = (unsigned long long int)(*(unsigned long int *)pholder->arg);
	else
		arg = *(unsigned long long int *)pholder->arg;
	pholder->converted_arg = ft_ullint_to_str_base(arg, base);
	apply_str_modifiers_uint(pholder, base);
	if (pholder->is_uppercase)
		ft_capitalize(pholder->converted_arg);
	pholder->arg_len = ft_strlen(pholder->converted_arg);
}
