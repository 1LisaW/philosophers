/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:40:04 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/15 09:29:40 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_ms_timestamp(struct timeval *tm_stamp)
{
	long	calc_ms;

	calc_ms = tm_stamp->tv_sec * 1000 + tm_stamp->tv_usec / 1000;
	return (calc_ms);
}

long	get_ms_diff(struct timeval *tm_ph, struct timeval *tm_stamp)
{
	long	calc_ms_diff;

	calc_ms_diff = get_ms_timestamp(tm_stamp) - get_ms_timestamp(tm_ph);
	return (calc_ms_diff);
}

int	is_dead_soul(t_philo *ph)
{
	int	is_dead_soul;

	if (!ph->is_dead_mtx)
		return (1);
	pthread_mutex_lock(ph->is_dead_mtx);
	is_dead_soul = *ph->is_dead_soul;
	pthread_mutex_unlock(ph->is_dead_mtx);
	return (is_dead_soul);
}

void	set_is_dead_soul(t_philo *ph, int is_dead_soul)
{
	pthread_mutex_lock(ph->is_dead_mtx);
	*ph->is_dead_soul = is_dead_soul;
	pthread_mutex_unlock(ph->is_dead_mtx);
}
