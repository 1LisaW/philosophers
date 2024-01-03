/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:55:46 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/03 03:05:43 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "unistd.h"
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>

enum e_philo_args
{
	number_of_philosophers,
	time_to_die,
	time_to_eat,
	time_to_sleep,
	number_of_times_each_philosopher_must_eat
};

typedef struct s_philo_args
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	int	have_oblig;
}		t_philo_args;

int		parse_args(t_philo_args *ph_args, int argc, char **argv);

void	*eat();

int		threads_generator(t_philo_args *philo_args);

#endif
