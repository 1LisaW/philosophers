/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:13:20 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/18 01:59:52 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_shared	*create_shared(t_philo_args *philo_args)
{
	t_shared		*shared;

	shared = NULL;
	shared = malloc(sizeof(t_shared));
	if (!shared)
		return (NULL);
	pthread_mutex_init(&shared->data_mtx, NULL);
	pthread_mutex_init(&shared->is_dead_mtx, NULL);
	shared->ph_nb = philo_args->number_of_philosophers;
	shared->detached_ph_nb = 0;
	shared->have_oblig = philo_args->have_oblig;
	shared->is_dead_soul = 0;
	shared->nb_meals = 0
		+ philo_args->number_of_times_each_philosopher_must_eat;
	shared->time_to_die = philo_args->time_to_die;
	shared->time_to_eat = philo_args->time_to_eat;
	shared->time_to_sleep = philo_args->time_to_sleep;
	return (shared);
}

static void	philo_init(t_philo	*philo_inst, int idx, t_shared *shared)
{
	philo_inst->nb = idx + 1;
	philo_inst->is_proceed = 1;
	philo_inst->fork_l = NULL;
	philo_inst->fork_r = NULL;
	philo_inst->has_eaten = 0;
	philo_inst->state = thinking;
	philo_inst->is_proceed_mtx = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo_inst->is_proceed_mtx, NULL);
	philo_inst->shared = shared;
}

void	create_philo(t_philo *philos_arr, int *idx, t_shared *shared)
{
	t_philo	philo_inst;

	philo_init(&philo_inst, *idx, shared);
	philos_arr[*idx] = philo_inst;
	gettimeofday(&philos_arr[*idx].timestemp_create, NULL);
	gettimeofday(&philos_arr[*idx].timestemp_eaten, NULL);
	create_forks(*idx, philos_arr, shared->ph_nb);
	pthread_create(&philos_arr[*idx].th, NULL, routine,
		(void *) &philos_arr[*idx]);
	*idx += 1;
}

t_philo	*create_philos(t_philo_args *philo_args, struct timeval *tm)
{
	t_philo			*philos_arr;
	t_shared		*shared;
	int				i;

	i = 0;
	philos_arr = NULL;
	shared = create_shared(philo_args);
	if (!philo_args->number_of_philosophers)
		return (NULL);
	philos_arr = malloc(sizeof(t_philo) * philo_args->number_of_philosophers);
	if (!philos_arr)
		return (NULL);
	while (i < philo_args->number_of_philosophers)
		create_philo(philos_arr, &i, shared);
	check_dead_condition(philos_arr, tm);
	i = 0;
	while (i < shared->ph_nb
		&& !get_shared_is_dead(shared))
	{
		if (is_proceed(&philos_arr[i]))
			if (pthread_join(philos_arr[i].th, NULL))
				return (philos_arr);
		i++;
	}
	return (philos_arr);
}
