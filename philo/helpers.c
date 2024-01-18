/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:40:04 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/18 22:47:42 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_ms_timestamp(struct timeval *tm_stamp)
{
	unsigned long	calc_ms;

	calc_ms = tm_stamp->tv_sec * 1000 + tm_stamp->tv_usec / 1000;
	return (calc_ms);
}

unsigned long	get_ms_diff(struct timeval *tm_ph, struct timeval *tm_stamp)
{
	unsigned long	tm_stamp_ms;
	unsigned long	tm_ph_ms;

	tm_ph_ms = get_ms_timestamp(tm_ph);
	tm_stamp_ms = get_ms_timestamp(tm_stamp);
	if (tm_ph_ms > tm_stamp_ms)
		return (0);
	else
		return (tm_stamp_ms - tm_ph_ms);
}

void	make_delay(unsigned long ms, t_philo *ph)
{
	struct timeval	start_tm;
	struct timeval	tm_val;

	gettimeofday(&start_tm, NULL);
	gettimeofday(&tm_val, NULL);
	while (is_proceed(ph) && get_ms_diff(&start_tm, &tm_val) < ms)
	{
		usleep(500);
		gettimeofday(&tm_val, NULL);
	}
}
