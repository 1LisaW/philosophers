/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 02:47:39 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/15 14:00:37 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_ms_sleep(t_philo	*ph, struct timeval *tm_stamp, int ms_diff)
{
	long			calc_ms_diff;
	struct timeval	tm_ph;

	calc_ms_diff = 0;
	tm_ph = ph->timestemp_eaten;
	while (is_proceed(ph) && ms_diff > calc_ms_diff)
	{
		usleep(500);
		gettimeofday(tm_stamp, NULL);
		calc_ms_diff = get_ms_diff(&tm_ph, tm_stamp);
	}
}

void	ft_sleep(t_philo *ph, struct timeval *tm)
{
	struct timeval	tm_start;

	if (!is_proceed(ph) || is_dead_soul(ph))
		return ;
	gettimeofday(&tm_start, NULL);
	gettimeofday(tm, NULL);
	ph->state = sleeping;
	if (is_proceed(ph))
		ft_print_info(ph, tm, sleeping, 0);
	while (is_proceed(ph) && get_ms_diff(&tm_start, tm) < ph->time_to_sleep)
	{
		usleep(500);
		gettimeofday(tm, NULL);
	}
	if (!is_proceed(ph) || is_dead_soul(ph))
		return ;
	ph->state = thinking;
	gettimeofday(&tm_start, NULL);
	ft_print_info(ph, tm, thinking, 0);
}

void	ft_eat(t_philo *ph, struct timeval *tm_stamp)
{
	if (ph->fork_l == ph->fork_r)
		return ;
	if (!is_proceed(ph) || is_dead_soul(ph))
		return ;
	if (take_forks(ph))
		return ;
	gettimeofday(tm_stamp, NULL);
	if (is_dead_soul(ph) || !is_proceed(ph))
		return (drop_forks(ph));
	// ft_print_info(ph, tm_stamp, thinking, 1);
	ft_print_info(ph, tm_stamp, thinking, 2);
	gettimeofday(&ph->timestemp_eaten, NULL);
	gettimeofday(tm_stamp, NULL);
	ph->state = eating;
	ft_print_info(ph, tm_stamp, eating, 0);
	ft_ms_sleep(ph, tm_stamp, ph->time_to_eat);
	drop_forks(ph);
	// ft_print_info(ph, tm_stamp, eating, 3);
	ph->has_eaten += 1;
	if (is_proceed(ph) && ph->have_oblig
		&& ph->has_eaten == ph->number_of_times_each_philosopher_must_eat)
		set_is_proceed(ph, 0);
	ft_sleep(ph, tm_stamp);
	return ;
}

void	*routine(void *philo)
{
	t_philo			*ph;
	struct timeval	tm_stamp;

	ph = (t_philo *)philo;
	gettimeofday(&tm_stamp, NULL);
	gettimeofday(&ph->timestemp_create, NULL);
	gettimeofday(&ph->timestemp_eaten, NULL);
	gettimeofday(&tm_stamp, NULL);
	while (!is_dead_soul(ph) && is_proceed(ph))
		// && (!ph->have_oblig || ph->has_eaten
		// < ph->number_of_times_each_philosopher_must_eat))
	{
		if (ph->state == thinking)
		{
			pthread_mutex_lock(&ph->run_mtx);
			ft_eat(ph, &tm_stamp);
			pthread_mutex_unlock(&ph->run_mtx);
		}
	}
	// if (is_proceed(ph))
	// 	set_is_proceed(ph, 0);
	pthread_detach(ph->th);
	return (NULL);
}
