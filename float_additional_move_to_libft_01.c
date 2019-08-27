/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_additional_move_to_libft_01.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 19:24:26 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/27 19:26:50 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char						*ft_join_str_array(char **array)
{
	size_t					len;
	char					*result;
	int						i;

	len = 0;
	i = 0;
	while (array[i])
		len += ft_strlen(array[i++]);
	if (!(result = ft_strnew(len + 1)))
		exit(EXIT_FAILURE);
	i = 0;
	while (*array)
	{
		ft_strcpy(result + i, *array);
		i += ft_strlen(*array);
		array++;
	}
	return (result);
}

char						*ft_join_strings(int str_num, ...)
{
	va_list					ap;
	char					*result;
	char					**args;
	int						i;

	va_start(ap, str_num);
	if (!(args = (char **)malloc(sizeof(char *) * (str_num + 1))))
		exit(EXIT_FAILURE);
	args[str_num] = NULL;
	i = 0;
	while (i < str_num)
		if (!(args[i++] = ft_strdup(va_arg(ap, char *))))
			return (NULL);
	va_end(ap);
	result = ft_join_str_array(args);
	ft_str_free_array(&args);
	return (result);
}

long double					ft_float_power(long double n, int power)
{
	long double				result;

	result = 1.L;
	if (power > 0)
		while (power--)
			result *= n;
	else if (power < 0)
		while (power++)
			result /= n;
	return (result);
}

