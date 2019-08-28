/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_calculations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 20:25:45 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 16:54:12 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		is_leap_year(short int year)
{
	return (!(year % 4) && ((year % 100) || !(year % 400)));
}

void			get_day_and_month(short int days, t_time *time)
{
	int			i;
	static int	months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	i = 0;
	if (is_leap_year(time->year))
		months[1] = 29;
	else
		months[1] = 28;
	while (days > months[i])
		days -= months[i++];
	time->month = i + 1;
	time->day = days;
}

char			*get_wday(int day)
{
	static char	*wdays[7] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};
	
	return (wdays[day]);
}

t_time			*calculate_date_and_time(int epoch_time)
{
	t_time		*time;
	int			leap_years_to_date;
	int			days_since_epoch;
	int			days_this_year;
	int			seconds_this_day;

	time = (t_time *)ft_malloc_or_exit(sizeof(t_time));
	time->epoch_time = epoch_time;
	time->year = 1970 + time->epoch_time / SECONDS_IN_A_YEAR;
	leap_years_to_date = (time->year - 1969) / 4;
	days_since_epoch = time->epoch_time / SECONDS_IN_A_DAY;
	days_this_year = (days_since_epoch + 1 - leap_years_to_date) % 365;
	get_day_and_month(days_this_year, time);
	time->wday = get_wday((days_since_epoch + 3 * SECONDS_IN_A_DAY) % 7);
	seconds_this_day = time->epoch_time - (days_since_epoch * SECONDS_IN_A_DAY);
	time->hour = seconds_this_day / 3600;
	time->minute = (seconds_this_day - (time->hour * 3600)) / 60;
	time->second = (seconds_this_day - (time->hour * 3600)) -
					(time->minute * 60);
	return (time);
}

char			*convert_with_nessesery_zero(unsigned char num)
{
	char		*temp;
	char		*result;

	temp = ft_itoa(num);
	if (num < 10)
	{
		result = ft_strnew(3);
		result[0] = '0';
		result[1] = *temp;
		ft_strdel(&temp);
	}
	else
		result = temp;
	return (result);
}
