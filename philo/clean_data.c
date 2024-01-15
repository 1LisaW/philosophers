/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 02:41:04 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/15 14:02:59 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	destroy_first_philo(t_philo *philos, int size)
{
	pthread_mutex_lock(&philos[0].run_mtx);
	if (size > 1)
		pthread_mutex_lock(&philos[1].run_mtx);
	if (size > 2)
		pthread_mutex_lock(&philos[size - 1].run_mtx);
	pthread_mutex_destroy(philos[0].is_proceed_mtx);
	free(philos[0].is_proceed_mtx);
	pthread_mutex_destroy(philos[0].fork_r);
	if (size > 1)
		pthread_mutex_destroy(philos[0].fork_l);
	free(philos[0].fork_l);
	philos[0].fork_l = NULL;
	if (size > 1)
		free(philos[0].fork_r);
	philos[0].fork_r = NULL;
	pthread_mutex_unlock(&philos[0].run_mtx);
	if (size > 1)
		pthread_mutex_unlock(&philos[1].run_mtx);
	if (size > 2)
	pthread_mutex_unlock(&philos[size - 1].run_mtx);
}

static void	destroy_philos(t_philo **philos_arr, int size)
{
	int		i;
	t_philo	*philos;

	philos = *philos_arr;
	i = 1;
	if (!size)
		return ;
	usleep(500);
	destroy_first_philo(philos, size);
	while (i < size - 1)
	{
		pthread_mutex_lock(&philos[i].run_mtx);
		if (i < size - 2)
			pthread_mutex_lock(&philos[i + 1].run_mtx);
		else
			pthread_mutex_lock(&philos[0].run_mtx);
		// pthread_mutex_destroy(philos[i].is_proceed_mtx);
		pthread_mutex_destroy(philos[i].fork_r);
		philos[i].fork_l = NULL;
		free(philos[i].fork_r);
		// free(philos[i].is_proceed_mtx);
		philos[i].fork_r = NULL;
		pthread_mutex_unlock(&philos[i].run_mtx);
		if (i < size - 2)
			pthread_mutex_unlock(&philos[i + 1].run_mtx);
		else
			pthread_mutex_unlock(&philos[0].run_mtx);
		// philos[i].is_proceed_mtx = NULL;
		i++;
	}
	// free(philos[0].is_dead_soul);
}

void	clean_data(t_philo *philos_arr, t_philo_args *philo_args)
{
	int		amount_of_proceed;
	int		i;

	amount_of_proceed = philo_args->number_of_philosophers;
	if (!philo_args->number_of_philosophers)
		return ;
	while (amount_of_proceed)
	{
		i = 0;
		amount_of_proceed = 0;
		while (i < philo_args->number_of_philosophers)
		{
			amount_of_proceed += is_proceed(&philos_arr[i]);
			i++;
		}
		printf("\n NOT ALL DONE: %i\n", amount_of_proceed);
	}
	destroy_philos(&philos_arr, philo_args->number_of_philosophers);
	// pthread_mutex_destroy(philos_arr[0].is_dead_mtx);
	// philos_arr[0].is_dead_mtx = NULL;
	// philos_arr[0].is_dead_soul = NULL;
	pthread_mutex_lock(&philos_arr[0].run_mtx);
	free(philo_args);
	pthread_mutex_unlock(&philos_arr[0].run_mtx);
	pthread_mutex_destroy(&philos_arr[0].run_mtx);
}
