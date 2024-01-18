/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:00:59 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/19 02:08:17 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_shared_is_dead(t_shared *shared)
{
	int	is_dead;

	pthread_mutex_lock(&shared->is_dead_mtx);
	is_dead = shared->is_dead_soul;
	pthread_mutex_unlock(&shared->is_dead_mtx);
	return (is_dead);
}

void	set_shared_is_dead(t_shared *shared, int is_dead)
{
	pthread_mutex_lock(&shared->is_dead_mtx);
	shared->is_dead_soul = is_dead;
	pthread_mutex_unlock(&shared->is_dead_mtx);
}

int	get_shared_detached(t_shared *shared)
{
	int	detached_ph_nb;

	pthread_mutex_lock(&shared->data_mtx);
	detached_ph_nb = shared->detached_ph_nb;
	pthread_mutex_unlock(&shared->data_mtx);
	return (detached_ph_nb);
}

void	inc_shared_detached(t_shared *shared)
{
	pthread_mutex_lock(&shared->data_mtx);
	shared->detached_ph_nb += 1;
	pthread_mutex_unlock(&shared->data_mtx);
}

void	fill_shared_from_args(t_philo_args *philo_args, t_shared *shared)
{
	shared->ph_nb = philo_args->number_of_philosophers;
	shared->detached_ph_nb = 0;
	shared->have_oblig = philo_args->have_oblig;
	shared->is_dead_soul = 0;
	shared->nb_meals = 0
		+ philo_args->number_of_times_each_philosopher_must_eat;
	shared->time_to_die = philo_args->time_to_die;
	shared->time_to_eat = philo_args->time_to_eat;
	shared->time_to_sleep = philo_args->time_to_sleep;
}
