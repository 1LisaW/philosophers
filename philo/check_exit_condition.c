/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_condition.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 00:01:26 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/18 18:59:50 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_proceed(t_philo *ph)
{
	int	is_proceed;

	pthread_mutex_lock(ph->is_proceed_mtx);
	is_proceed = ph->is_proceed;
	pthread_mutex_unlock(ph->is_proceed_mtx);
	return (is_proceed);
}

void	set_is_proceed(t_philo *ph, int is_proceed)
{
	pthread_mutex_lock(ph->is_proceed_mtx);
	ph->is_proceed = is_proceed;
	printf("\nchanged is_proceed %i\n", ph->nb);
	pthread_mutex_unlock(ph->is_proceed_mtx);
}

void	check_ph_on_stop(t_philo *philos_arr, int i,
			struct timeval *tm)
{
	t_shared	*shared;
	unsigned long	time;

	shared = philos_arr[i].shared;
	gettimeofday(tm, NULL);
	if (is_proceed(&philos_arr[i]) && get_shared_is_dead(shared))
		set_is_proceed(&philos_arr[i], 0);
	gettimeofday(tm, NULL);
	// printf("\n\n",);
	pthread_mutex_lock(philos_arr[i].is_proceed_mtx);
	time =  get_ms_diff(&philos_arr[i].timestemp_eaten, tm);
	pthread_mutex_unlock(philos_arr[i].is_proceed_mtx);
	// if (time > 800)
	// 	printf("\nnb %i, eaten time %li, tmstamp %li\n", i, get_ms_timestamp(&philos_arr[i].timestemp_eaten), get_ms_timestamp(tm));
	if (is_proceed(&philos_arr[i]) && (unsigned long)shared->time_to_die
		< time
		&& !get_shared_is_dead(shared))
	{
		printf("\n get_shared_is_dead(shared) (%i),shared->time_to_die (%i) \n, &philos_arr[i].timestemp_eaten(%li), tm (%li)\n, get_ms_diff(&philos_arr[i].timestemp_eaten, tm)(%li), shared->time_to_die < get_ms_diff(&philos_arr[i].timestemp_eaten, tm) (%i)\n",
		get_shared_is_dead(shared),
		shared->time_to_die,
		get_ms_timestamp(&philos_arr[i].timestemp_eaten),
		get_ms_timestamp(tm),
		time,
		(unsigned long)shared->time_to_die	< time);
		set_shared_is_dead(shared, 1);
		set_is_proceed(&philos_arr[i], 0);
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
