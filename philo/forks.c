/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 07:06:11 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/19 00:00:11 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	create_right_fork(int idx, t_philo *philos_arr)
{
	pthread_mutex_t	mutex_r;

	pthread_mutex_init(&mutex_r, NULL);
	philos_arr[idx].fork_r = malloc(sizeof(pthread_mutex_t));
	*philos_arr[idx].fork_r = mutex_r;
}

void	create_forks(int idx, t_philo *philos_arr, int philo_amount)
{
	pthread_mutex_t	mutex_l;

	if (!idx)
	{
		pthread_mutex_init(&mutex_l, NULL);
		philos_arr[idx].fork_l = malloc(sizeof(pthread_mutex_t));
		*philos_arr[idx].fork_l = mutex_l;
		if (philo_amount > 1)
			create_right_fork(idx, philos_arr);
		else
			philos_arr[idx].fork_r = philos_arr[0].fork_l;
	}
	else
	{
		philos_arr[idx].fork_l = philos_arr[idx - 1].fork_r;
		if (idx + 1 == philo_amount)
			philos_arr[idx].fork_r = philos_arr[0].fork_l;
		else
			create_right_fork(idx, philos_arr);
	}
}

int	take_forks(t_philo *ph)
{
	if (ph->nb % 2)
	{
		// if (ph->shared->ph_nb % 2)
		// 	usleep((1 + (ph->nb - 1) % 3) * 50);
		pthread_mutex_lock(ph->fork_r);
		pthread_mutex_lock(ph->fork_l);
	}
	else
	{
		// if (ph->shared->ph_nb % 2)
		// 	usleep((1 + (ph->nb - 1) % 3) * 50);
		pthread_mutex_lock(ph->fork_l);
		pthread_mutex_lock(ph->fork_r);
	}
	// else
	// {
	// 	usleep((1 + (ph->nb - 1) % 3) * 10);
	// 	pthread_mutex_lock(ph->fork_l);
	// 	pthread_mutex_lock(ph->fork_r);
	// }
	return (0);
}

void	drop_forks(t_philo *ph)
{
	if (ph->nb % 2)
	{
		pthread_mutex_unlock(ph->fork_r);
		// if (ph->shared->ph_nb % 2 == 0)
		// 	usleep(200);
		pthread_mutex_unlock(ph->fork_l);
		usleep(200);
	}
	else
	{
		pthread_mutex_unlock(ph->fork_l);
		// if (ph->shared->ph_nb % 2 == 0)
		// 	usleep(200);
		pthread_mutex_unlock(ph->fork_r);
		usleep(200);
	}
	// else
	// {
	// 	pthread_mutex_unlock(ph->fork_l);
	// 	pthread_mutex_unlock(ph->fork_r);
	// }
}
