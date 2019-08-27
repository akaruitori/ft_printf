/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 23:21:36 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/27 20:39:38 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <float.h>
#include <stdint.h>
#include <stdlib.h>
# include <stdarg.h>

char				*ft_strnew(size_t size);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *str);
long long int		ft_abs(long long int n);
void				ft_strdel(char **as);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
void				ft_memdel(void **ap);
void				ft_str_free_array(char ***array);
char				*ft_itoa(int n);
void				ft_bzero(void *s, size_t n);
char				*ft_llint_to_str_base(long long int num, int base);
char				*ft_ullint_to_str_base(unsigned long long int num, int base);

void				ft_capitalize(char *s)
{
	while (*s)
	{
		if (ft_isalpha(*s))
			*s = ft_toupper(*s);
		s++;
	}
}

void				convert_nan(t_pholder *pholder, long double num)
{
	unsigned char	bits[8];

	ft_memcpy((void *)bits, (void *)&num, 8);
	if (bits[0] & 0x80)
		pholder->converted_arg = ft_strcpy(ft_strnew(4), "-nan");
	else
		pholder->converted_arg = ft_strcpy(ft_strnew(5), "nan");
	
}

void		convert_inf(t_pholder *pholder, long double num)
{
	if (num > 0)
		pholder->converted_arg = ft_strcpy(ft_strnew(4), "inf");
	else
		pholder->converted_arg = ft_strcpy(ft_strnew(5), "-inf");
}

void		convert_float(t_pholder *pholder)
{
	long double		num;

	num = get_long_double_num(pholder);
	if (ft_is_inf(num))
		convert_inf(pholder, num);
	else if (ft_is_nan(num))
		convert_nan(pholder, num);
	else if (pholder->arg_type->is_hex)
	{
		if (pholder->modifier && pholder->modifier->is_big_l)
			convert_long_double_hex(pholder);
		else
			convert_double_hex(pholder);
	}
	else if (pholder->arg_type->is_full_form)
		convert_float_full(num, pholder);
	else if (pholder->arg_type->is_exp_form)
		convert_float_exp(num, pholder);
	else if (pholder->arg_type->is_opt_form)
		convert_float_opt(num, pholder);
	apply_str_modifiers_float(pholder, num);
	if (pholder->is_uppercase)
		ft_capitalize(pholder->converted_arg);
	pholder->arg_len = ft_strlen(pholder->converted_arg);
}
