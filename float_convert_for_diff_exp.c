/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_convert_for_diff_exp.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:50:42 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 16:56:47 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char						*fractional_part_to_str(long double num,
							int current_order, t_pholder *pholder)
{
	int						num_dig;
	char					*temp;
	int						precision;
	int						i;

	num_dig = (pholder->modifier && pholder->modifier->is_big_l ?
				LDBL_DIG - current_order : DBL_DIG - current_order);
	if (pholder->precision && pholder->precision->value >= 0)
		precision = pholder->precision->value;
	else
		precision = 6;
	if (!(temp = ft_strnew(precision + 2)))
		malloc_error_exit();
	i = 0;
	if (precision > 0 || (pholder->flags && pholder->flags->alt_form))
		temp[i++] = '.';
	while (precision--)
	{
		num *= 10.l;
		temp[i++] = (num_dig > 0 ? ((int)num % 10 + 48) : '0');
		num -= (int)num;
		num_dig--;
	}
	return (temp);
}

void						convert_huge_float_full(long double num,
													t_pholder *pholder)
{
	int						order;
	int						num_dig;
	int						i;
	char					*temp;
	char					*temp_str_fraction;

	order = get_float_order(num);
	num /= ft_float_power(10.l, order - 1);
	temp = (char *)ft_malloc_or_exit(sizeof(char) * (order + 1));
	temp[order] = '\0';
	num_dig = (pholder->modifier && pholder->modifier->is_big_l ?
				LDBL_DIG : DBL_DIG);
	i = 0;
	while (order--)
	{
		temp[i++] = (num_dig <= 0 ? '0' : ((int)num + 48));
		num = (num - (int)num) * 10.l;
		num_dig--;
	}
	temp_str_fraction = fractional_part_to_str(num, ft_strlen(temp), pholder);
	pholder->converted_arg = ft_strjoin(temp, temp_str_fraction);
	ft_strdel(&temp);
	ft_strdel(&temp_str_fraction);
}

void						convert_medium_float_full(long double num,
														t_pholder *pholder)
{
	unsigned long long int	integer;
	char					*temp_str_integer;
	char					*temp_str_fraction;

	integer = (unsigned long long)num;
	num -= integer;
	temp_str_integer = ft_ullint_to_str_base(integer, 10);
	if (!temp_str_integer || !(temp_str_fraction =
		fractional_part_to_str(num, ft_strlen(temp_str_integer), pholder)))
		malloc_error_exit();
	pholder->converted_arg = ft_strjoin(temp_str_integer, temp_str_fraction);
	ft_strdel(&temp_str_integer);
	ft_strdel(&temp_str_fraction);
}

void						convert_small_float_full(long double num,
												t_pholder *pholder)
{
	char					*temp;

	temp = fractional_part_to_str(num, 0, pholder);
	pholder->converted_arg = ft_strjoin("0", temp);
	ft_strdel(&temp);
}
