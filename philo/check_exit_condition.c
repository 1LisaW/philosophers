/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_condition.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 00:01:26 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/19 02:02:14 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_proceed(t_philo *ph)
{
	int	is_proceed;

	pthread_mutex_lock(ph->is_proceed_mtx);
	if (ph->shared->dead_flags[ph->nb - 1])
		is_proceed = 0;
	else
		is_proceed = ph->is_proceed;
	pthread_mutex_unlock(ph->is_proceed_mtx);
	return (is_proceed);
}

void	set_is_proceed(t_philo *ph, int is_proceed)
{
	pthread_mutex_lock(ph->is_proceed_mtx);
	ph->is_proceed = is_proceed;
	pthread_mutex_unlock(ph->is_proceed_mtx);
}

static void	fill_death_flags(t_philo *philos_arr, t_shared *shared)
{
	int				idx;

	idx = 0;
	while (idx < shared->ph_nb)
	{
		pthread_mutex_lock(philos_arr[idx].is_proceed_mtx);
		shared->dead_flags[idx] = 1;
		pthread_mutex_unlock(philos_arr[idx].is_proceed_mtx);
		idx++;
	}
}

void	check_ph_on_stop(t_philo *philos_arr, int i,
			struct timeval *tm)
{
	t_shared		*shared;
	unsigned long	time;

	shared = philos_arr[i].shared;
	gettimeofday(tm, NULL);
	if (get_shared_is_dead(shared) && is_proceed(&philos_arr[i]))
		set_is_proceed(&philos_arr[i], 0);
	gettimeofday(tm, NULL);
	pthread_mutex_lock(philos_arr[i].is_proceed_mtx);
	time = get_ms_diff(&philos_arr[i].timestemp_eaten, tm);
	pthread_mutex_unlock(philos_arr[i].is_proceed_mtx);
	if (is_proceed(&philos_arr[i]) && (unsigned long)shared->time_to_die
		< time
		&& !get_shared_is_dead(shared))
	{
		set_shared_is_dead(shared, 1);
		set_is_proceed(&philos_arr[i], 0);
		fill_death_flags(philos_arr, shared);
		ft_print_info(&philos_arr[i], tm, dead, 0);
	}
}

void	check_dead_condition(t_philo *philos_arr, struct timeval *tm)
{
	t_shared	*shared;
	int			i;

	shared = philos_arr[0].shared;
	while (get_shared_detached(shared) < shared->ph_nb)
	{
		i = 0;
		while (i < shared->ph_nb && get_shared_detached(shared)
			< shared->ph_nb)
		{
			gettimeofday(tm, NULL);
			check_ph_on_stop(philos_arr, i, tm);
			i++;
			if (get_shared_detached(shared) == shared->ph_nb)
				break ;
		}
	}
}
