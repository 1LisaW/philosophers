/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:51:27 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/18 04:08:18 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo_args	*ph_args;
	t_philo			*philo_arr;
	struct timeval	tm;

	philo_arr = NULL;
	ph_args = NULL;
	ph_args = malloc(sizeof(t_philo_args));
	if (parse_args(ph_args, argc, argv))
		return (1);
	philo_arr = create_philos(ph_args, &tm);
	free(ph_args);
	clean_data(philo_arr);
	return (0);
}
