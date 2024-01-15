/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:13:20 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/15 11:52:09 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_init(t_philo	*philo_inst, int idx, t_philo_args *philo_args)
{
	philo_inst->nb = idx + 1;
	philo_inst->is_proceed = 1;
	philo_inst->is_dead_soul = NULL;
	philo_inst->fork_l = NULL;
	philo_inst->fork_r = NULL;
	philo_inst->time_to_die = philo_args->time_to_die;
	philo_inst->time_to_eat = philo_args->time_to_eat;
	philo_inst->time_to_sleep = philo_args->time_to_sleep;
	philo_inst->have_oblig = philo_args->have_oblig;
	philo_inst->number_of_times_each_philosopher_must_eat
		= philo_args->number_of_times_each_philosopher_must_eat;
	philo_inst->has_eaten = 0;
	philo_inst->state = thinking;
	philo_inst->is_proceed_mtx = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo_inst->is_proceed_mtx, NULL);
}

void	create_philo(t_philo *philos_arr, int *idx, t_philo_args *philo_args)
{
	t_philo	philo_inst;

	philo_init(&philo_inst, *idx, philo_args);
	philos_arr[*idx] = philo_inst;
	if (*idx == 0)
	{
		philos_arr[*idx].is_dead_soul = malloc(sizeof(int));
		*philos_arr[*idx].is_dead_soul = 0;
		philos_arr[*idx].is_dead_mtx = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philos_arr[*idx].is_dead_mtx, NULL);
	}
	else
	{
		philos_arr[*idx].is_dead_soul = philos_arr[0].is_dead_soul;
		philos_arr[*idx].is_dead_mtx = philos_arr[0].is_dead_mtx;
	}
	pthread_mutex_init(&philos_arr[*idx].run_mtx, NULL);
	gettimeofday(&philos_arr[*idx].timestemp_create, NULL);
	gettimeofday(&philos_arr[*idx].timestemp_eaten, NULL);
	create_forks(*idx, philos_arr, philo_args->number_of_philosophers);
	pthread_create(&philos_arr[*idx].th, NULL, routine,
		(void *) &philos_arr[*idx]);
	*idx += 1;
}

t_philo	*create_philos(t_philo_args *philo_args, struct timeval *tm)
{
	t_philo			*philos_arr;
	int				i;

	i = 0;
	philos_arr = NULL;
	if (!philo_args->number_of_philosophers)
		return (NULL);
	philos_arr = malloc(sizeof(t_philo) * philo_args->number_of_philosophers);
	if (!philos_arr)
		return (NULL);
	while (i < philo_args->number_of_philosophers)
		create_philo(philos_arr, &i, philo_args);
	check_dead_condition(philos_arr, philo_args, tm);
	i = 0;
	while (i < philo_args->number_of_philosophers
		&& !is_dead_soul(&philos_arr[0]))
	{
		if (is_proceed(&philos_arr[i]))
			if (pthread_join(philos_arr[i].th, NULL))
				return (philos_arr);
		i++;
	}
	return (philos_arr);
}
