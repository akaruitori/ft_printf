/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 00:38:39 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/27 20:28:39 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char				*time_to_str(t_time *time)
{
	char			*hour;
	char			*minute;
	char			*second;
	char			*result;

	hour = convert_with_nessesery_zero(time->hour);
	minute = convert_with_nessesery_zero(time->minute);
	second = convert_with_nessesery_zero(time->second);
	result = ft_join_strings(5, hour, ":", minute, ":", second);
	ft_strdel(&hour);
	ft_strdel(&minute);
	ft_strdel(&second);
	return (result);
}

char				*date_to_str(t_time *time)
{
	char			*year;
	char			*month;
	char			*day;
	char			*result;

	year = ft_itoa(time->year);
	month = convert_with_nessesery_zero(time->month);
	day = convert_with_nessesery_zero(time->day);
	result = ft_join_strings(5, day, ".", month, ".", year);
	ft_strdel(&year);
	ft_strdel(&month);
	ft_strdel(&day);
	return (result);
}

char				*date_time_to_str(t_time *time)
{
	char			*time_str;
	char			*date;
	char			*result;

	time_str = time_to_str(time);
	date = date_to_str(time);
	result = ft_join_strings(3, date, " ", time_str);
	ft_strdel(&time_str);
	ft_strdel(&date);
	return (result);
}

char				*full_date_time_to_str(t_time *time)
{
	char			*date_time;
	char			*wday;
	char			*result;

	wday = ft_strcpy(ft_strnew(4), time->wday);
	date_time = date_time_to_str(time);
	result = ft_join_strings(3, wday, ", ", date_time);
	ft_strdel(&wday);
	ft_strdel(&date_time);
	return (result);
}

void				convert_time(t_pholder *pholder)
{
	int				epoch_time;
	t_time			*time;

	epoch_time = ft_abs(*(int *)pholder->arg);
	time = calculate_date_and_time(epoch_time);
	if (!pholder->modifier)
		pholder->converted_arg = date_time_to_str(time);
	else if (pholder->modifier->is_h || pholder->modifier->is_hh)
		pholder->converted_arg = time_to_str(time);
	else
		pholder->converted_arg = full_date_time_to_str(time);
	if (pholder->width)
	{
		if (pholder->flags && pholder->flags->left_align)
			apply_width_left_align(pholder, ft_strlen(pholder->converted_arg));
		else
			apply_width(pholder, ft_strlen(pholder->converted_arg));
	}
	pholder->arg_len = ft_strlen(pholder->converted_arg);
}
