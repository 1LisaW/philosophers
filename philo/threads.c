/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:13:20 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/03 03:06:53 by tklimova         ###   ########.fr       */
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
