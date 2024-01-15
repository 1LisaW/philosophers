/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:55:46 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/15 11:51:19 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

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
	int					nb;
	pthread_t			th;
	pthread_mutex_t		run_mtx;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		*is_dead_mtx;
	int					*is_dead_soul;
	pthread_mutex_t		*is_proceed_mtx;
	int					is_proceed;
	enum e_philo_states	state;
	struct timeval		timestemp_create;
	struct timeval		timestemp_eaten;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	int					have_oblig;
	int					has_eaten;
}		t_philo;

int		parse_args(t_philo_args *ph_args, int argc, char **argv);

void	create_forks(int idx, t_philo *philos_arr, int philo_amount);

int		is_proceed(t_philo *ph);

void	set_is_proceed(t_philo *ph, int is_proceed);

int		is_dead_soul(t_philo *ph);

void	set_is_dead_soul(t_philo *ph, int is_dead_soul);

void	check_dead_condition(t_philo *philos_arr, t_philo_args *philo_args,
			struct timeval *tm);

int		take_forks(t_philo *ph);

void	drop_forks(t_philo *ph);

long	get_ms_timestamp(struct timeval *tm_stamp);

long	get_ms_diff(struct timeval *tm_ph, struct timeval *tm_stamp);

void	ft_print_info(t_philo *ph, struct timeval *timestamp,
			enum e_philo_states state, int fork_idx);

void	*routine(void *philo);

t_philo	*create_philos(t_philo_args *philo_args, struct timeval *tm);

void	clean_data(t_philo *philos_arr, t_philo_args *philo_args);

#endif
