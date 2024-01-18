/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 02:41:04 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/18 04:10:08 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	destroy_first_philo(t_philo *philos, int size)
{
	pthread_mutex_lock(&philos[0].shared->data_mtx);
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
	pthread_mutex_unlock(&philos[0].shared->data_mtx);
	philos[0].shared = NULL;
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
		pthread_mutex_destroy(philos[i].is_proceed_mtx);
		pthread_mutex_lock(&philos[i].shared->data_mtx);
		pthread_mutex_destroy(philos[i].fork_r);
		philos[i].fork_l = NULL;
		free(philos[i].fork_r);
		free(philos[i].is_proceed_mtx);
		philos[i].fork_r = NULL;
		pthread_mutex_unlock(&philos[i].shared->data_mtx);
		philos[i].shared = NULL;
		i++;
	}
}

void	clean_data(t_philo *philos_arr)
{
	t_shared	*shared;

	shared = philos_arr[0].shared;
	destroy_philos(&philos_arr, philos_arr->shared->ph_nb);
	pthread_mutex_destroy(&shared->is_dead_mtx);
	pthread_mutex_lock(&shared->data_mtx);
	free(philos_arr);
	pthread_mutex_unlock(&shared->data_mtx);
	pthread_mutex_destroy(&shared->data_mtx);
	free(shared);
}
