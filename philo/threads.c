/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:13:20 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/03 13:36:08 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	threads_generator(t_philo_args *philo_args)
{
	pthread_t	*thread_arr;
	int			i;
	int			philo_nb;

	i = 0;
	philo_nb = philo_args->number_of_philosophers;
	thread_arr = malloc(sizeof(pthread_t) * (philo_nb));
	while (i < philo_nb)
	{
		if (pthread_create(&thread_arr[i], (void *) NULL, &eat, (void *) NULL))
			return (1);
		i++;
	}
	i = 0;
	while (i < philo_nb)
	{
		if (pthread_join(thread_arr[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

void	create_forks(int idx, t_philo *philos_arr, int last_idx)
{
	pthread_mutex_t	*mutex_l;
	pthread_mutex_t	*mutex_r;
	t_philo			philo;

	philo = philos_arr[idx];
	if (idx)
	{
		philo.fork_l = philos_arr[idx - 1].fork_r;
		if (idx + 1 == last_idx)
			philos_arr[idx].fork_r = philos_arr[0].fork_l;
		else
		{
			pthread_mutex_init(&mutex_r, NULL);
			philo.fork_r = &mutex_r;
		}
	}
	else
	{
		pthread_mutex_init(&mutex_l, NULL);
		philo.fork_l = &mutex_l;
	}
	if (idx + 1 == last_idx)
		philos_arr[idx].fork_r = philos_arr[0].fork_l;
	
}

void	create_philo(t_philo *philos_arr, int idx, t_philo_args *philo_args)
{
	t_philo	philo_inst;

	if (!idx)
	{
		
	}
	if (idx + 1 == philo_args->number_of_philosophers)
		philo_inst.fork_r = philos_arr[0].fork_l;
	else if (!idx)
	{
		//create left
		//create right
	}
	else
		philo_inst.fork_l = philos_arr[idx - 1].fork_r;
	
}

int	create_philos(t_philo_args *philo_args)
{
	t_philo	*philos_arr;
	int		i;

	i = 0;
	philos_arr = malloc(sizeof(t_philo) * philo_args->number_of_philosophers);
	if (!philos_arr)
		return (1);
	while (i < philo_args->number_of_philosophers)
	{
		create_philo(philos_arr, i, parse_args);
		i++;
	}
	
}