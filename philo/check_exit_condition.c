/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_condition.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 00:01:26 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/15 13:05:16 by tklimova         ###   ########.fr       */
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
	pthread_mutex_unlock(ph->is_proceed_mtx);
}

void	check_ph_on_stop(t_philo *philos_arr, int i,
			struct timeval *tm, int *ph_finished)
{
	if (is_proceed(&philos_arr[i]) && is_dead_soul(&philos_arr[i]))
	{
		set_is_proceed(&philos_arr[i], 0);
		// pthread_detach(philos_arr[i].th);
	}
	// gettimeofday(tm, NULL);
	if (is_proceed(&philos_arr[i]) && philos_arr[i].time_to_die
		< get_ms_diff(&philos_arr[i].timestemp_eaten, tm)
		&& !is_dead_soul(&philos_arr[0]))
	{
		// gettimeofday(tm, NULL);
		set_is_dead_soul(&philos_arr[i], 1);
		printf("\n****SETTED DEAD CONDITION*****\n");
		set_is_proceed(&philos_arr[i], 0);
		ft_print_info(&philos_arr[i], tm, dead, 0);
		// pthread_detach(philos_arr[i].th);
	}
	if (!is_proceed(&philos_arr[i]))
		*ph_finished = *ph_finished + 1;
}

void	check_dead_condition(t_philo *philos_arr, t_philo_args *philo_args,
			struct timeval *tm)
{
	int	i;
	int	ph_finished;

	ph_finished = 0;
	while (ph_finished
		< philo_args->number_of_philosophers)
	{
		i = 0;
		ph_finished = 0;
		gettimeofday(tm, NULL);
		while (i < philo_args->number_of_philosophers
			&& ph_finished < philo_args->number_of_philosophers)
		{
			check_ph_on_stop(philos_arr, i, tm, &ph_finished);
			i++;
		}
	}
}
