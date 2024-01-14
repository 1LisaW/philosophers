/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 02:47:39 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/15 00:14:01 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static int	is_proceed(t_philo *ph, struct timeval *tm_stamp)
// {
// 	gettimeofday(tm_stamp, NULL);
// 	if (!ph->is_proceed)
// 		return (0);
// 	if (ph->have_oblig && ph->has_eaten
// 		>= ph->number_of_times_each_philosopher_must_eat)
// 		ph->is_proceed = 0;
// 	if (ph->is_proceed && get_ms_diff(&ph->timestemp_eaten, tm_stamp)
// 		> ph->time_to_die)
// 	{
// 		ph->state = dead;
// 		*ph->is_dead_soul = 1;
// 		ph->is_proceed = 0;
// 	}
// 	if (*ph->is_dead_soul && ph->is_proceed)
// 		ph->is_proceed = 0;
// 	if (!ph->is_proceed)
// 		pthread_detach(ph->th);
// 	return (ph->is_proceed);
// }

void	ft_ms_sleep(t_philo	*ph, struct timeval *tm_stamp, int ms_diff)
{
	long			calc_ms_diff;
	struct timeval	tm_ph;

	calc_ms_diff = 0;
	tm_ph = ph->timestemp_eaten;
	while (is_proceed(ph, tm_stamp) && ms_diff > calc_ms_diff)
	{
		usleep(500);
		gettimeofday(tm_stamp, NULL);
		calc_ms_diff = get_ms_diff(&tm_ph, tm_stamp);
	}
}

void	ft_sleep(t_philo *ph, struct timeval *tm)
{
	struct timeval	tm_start;

	gettimeofday(&tm_start, NULL);
	gettimeofday(tm, NULL);
	ph->state = sleeping;
	if (is_proceed(ph, tm))
		ft_print_info(ph, tm, sleeping, 0);
	while (is_proceed(ph, tm) && get_ms_diff(&tm_start, tm) < ph->time_to_sleep)
	{
		usleep(500);
		gettimeofday(tm, NULL);
	}
	if (*ph->is_dead_soul || (ph->have_oblig && ph->has_eaten
			== ph->number_of_times_each_philosopher_must_eat))
		return ;
	ph->state = thinking;
	gettimeofday(&tm_start, NULL);
	ft_print_info(ph, tm, thinking, 0);
}

void	ft_eat(t_philo *ph, struct timeval *tm_stamp)
{
	if (ph->state != thinking)
		return ;
	if (ph->fork_l == ph->fork_r || !is_proceed(ph, tm_stamp))
		return ;
	take_forks(ph);
	gettimeofday(tm_stamp, NULL);
	if (!is_proceed(ph, tm_stamp))
		return ;
	ft_print_info(ph, tm_stamp, thinking, 1);
	ft_print_info(ph, tm_stamp, thinking, 2);
	gettimeofday(&ph->timestemp_eaten, NULL);
	ph->state = eating;
	ft_print_info(ph, tm_stamp, eating, 0);
	ft_ms_sleep(ph, tm_stamp, ph->time_to_eat);
	pthread_mutex_unlock(ph->fork_l);
	pthread_mutex_unlock(ph->fork_r);
	ft_print_info(ph, tm_stamp, eating, 3);
	ph->has_eaten += 1;
	if (ph->state == eating)
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
	while (is_proceed(ph, &tm_stamp))
	{
		if (ph->state == thinking && ph->is_proceed)
			ft_eat(ph, &tm_stamp);
	}
	pthread_detach(ph->th);
	return (NULL);
}
