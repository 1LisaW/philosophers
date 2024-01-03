/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:51:27 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/03 03:46:01 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo_args	*ph_args;
	pthread_mutex_t	*mutex;

	pthread_mutex_init(&mutex, NULL);
	ph_args = malloc(sizeof(t_philo_args));
	if (parse_args(ph_args, argc, argv))
		return (1);
	threads_generator(ph_args);
	pthread_mutex_destroy(&mutex);
}
