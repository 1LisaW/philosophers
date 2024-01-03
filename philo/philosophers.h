/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:55:46 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/03 11:34:19 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "unistd.h"
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>

enum e_philo_states
{
	thinking,
	eating,
	sleeping,
	dead,
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

typedef struct s_philo
{
	pthread_t		*th;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	e_philo_states	state;
	int				timestemp;
}		t_philo;


int		parse_args(t_philo_args *ph_args, int argc, char **argv);

void	*eat();

int		threads_generator(t_philo_args *philo_args);

#endif
