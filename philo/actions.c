/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 02:47:39 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/18 23:57:30 by tklimova         ###   ########.fr       */
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

	if (!is_proceed(ph) || get_shared_is_dead(ph->shared))
		return ;
	gettimeofday(&tm_start, NULL);
	gettimeofday(tm, NULL);
	ph->state = sleeping;
	if (is_proceed(ph))
		ft_print_info(ph, tm, sleeping, 0);
	while (is_proceed(ph) && get_ms_diff(&tm_start, tm)
		< (unsigned long)ph->shared->time_to_sleep)
	{
		usleep(50);
		gettimeofday(tm, NULL);
	}
	if (!is_proceed(ph) || get_shared_is_dead(ph->shared))
		return ;
	ph->state = thinking;
	gettimeofday(tm, NULL);
	ft_print_info(ph, tm, thinking, 0);
	// if (ph->shared->ph_nb % 2 && ph->shared->time_to_eat > ph->shared->time_to_sleep)
	// 	make_delay(ph->shared->time_to_eat -  ph->shared->time_to_sleep, ph);
	// if (ph->shared->ph_nb % 2 == 0)
	// 	make_delay(50, ph);
	// else if (ph->shared->time_to_eat >= ph->shared->time_to_sleep)
	// 	make_delay(ph->shared->time_to_eat -  ph->shared->time_to_sleep + 10, ph);
}

void	ft_eat(t_philo *ph, struct timeval *tm_stamp)
{
	if (ph->fork_l == ph->fork_r)
		return ;
	if (!is_proceed(ph) || get_shared_is_dead(ph->shared))
		return ;
	if (take_forks(ph))
		return ;
	gettimeofday(tm_stamp, NULL);
	if (get_shared_is_dead(ph->shared) || !is_proceed(ph))
		return (drop_forks(ph));
	gettimeofday(tm_stamp, NULL);
	ft_print_info(ph, tm_stamp, thinking, 1);
	ft_print_info(ph, tm_stamp, thinking, 2);
	pthread_mutex_lock(ph->is_proceed_mtx);
	gettimeofday(&ph->timestemp_eaten, NULL);
	pthread_mutex_unlock(ph->is_proceed_mtx);
	gettimeofday(tm_stamp, NULL);
	ph->state = eating;
	ft_print_info(ph, tm_stamp, eating, 0);
	ft_ms_sleep(ph, tm_stamp, ph->shared->time_to_eat);
	drop_forks(ph);
	// ft_print_info(ph, tm_stamp, eating, 3);
	ph->has_eaten += 1;
	if (ph->shared->have_oblig
		&& ph->has_eaten == ph->shared->nb_meals && is_proceed(ph))
		set_is_proceed(ph, 0);
	ft_sleep(ph, tm_stamp);
	return ;
}

void	*routine(void *philo)
{
	t_philo			*ph;
	struct timeval	tm_stamp;

	ph = (t_philo *)philo;
	gettimeofday(&ph->timestemp_create, NULL);
	gettimeofday(&ph->timestemp_eaten, NULL);
	gettimeofday(&tm_stamp, NULL);
	if (ph->shared->ph_nb % 2)
		usleep(500 * (ph->nb - 1) % 3);
	else
		make_delay(10 * (ph->nb - 1) % 2, ph);
	while (!get_shared_is_dead(ph->shared) && is_proceed(ph))
	{
		if (ph->state == thinking)
		{
			ft_eat(ph, &tm_stamp);
		}
	}
	inc_shared_detached(ph->shared);
	pthread_mutex_lock(&ph->shared->data_mtx);
	pthread_detach(ph->th);
	pthread_mutex_unlock(&ph->shared->data_mtx);
	return (NULL);
}
