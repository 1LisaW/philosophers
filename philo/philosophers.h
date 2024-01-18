/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:55:46 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/19 02:10:13 by tklimova         ###   ########.fr       */
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

typedef struct s_shared
{
	pthread_mutex_t	data_mtx;
	pthread_mutex_t	is_dead_mtx;
	int				ph_nb;
	int				is_dead_soul;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				have_oblig;
	int				nb_meals;
	int				detached_ph_nb;
	int				*dead_flags;
}		t_shared;

typedef struct s_philo
{
	int					nb;
	pthread_t			th;
	pthread_mutex_t		run_mtx;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		*is_proceed_mtx;
	int					is_proceed;
	enum e_philo_states	state;
	struct timeval		timestemp_create;
	struct timeval		timestemp_eaten;
	int					has_eaten;
	t_shared			*shared;
}		t_philo;

void			fill_shared_from_args(t_philo_args *philo_args,
					t_shared *shared);

int				get_shared_is_dead(t_shared *shared);

void			set_shared_is_dead(t_shared *shared, int is_dead);

int				get_shared_detached(t_shared *shared);

void			inc_shared_detached(t_shared *shared);

int				parse_args(t_philo_args *ph_args, int argc, char **argv);

void			create_forks(int idx, t_philo *philos_arr, int philo_amount);

int				is_proceed(t_philo *ph);

void			set_is_proceed(t_philo *ph, int is_proceed);

void			check_dead_condition(t_philo *philos_arr, struct timeval *tm);

int				take_forks(t_philo *ph);

void			drop_forks(t_philo *ph);

unsigned long	get_ms_timestamp(struct timeval *tm_stamp);

unsigned long	get_ms_diff(struct timeval *tm_ph, struct timeval *tm_stamp);

void			make_delay(unsigned long ms, t_philo *ph);

void			ft_print_info(t_philo *ph, struct timeval *timestamp,
					enum e_philo_states state, int fork_idx);

void			*routine(void *philo);

t_philo			*create_philos(t_philo_args *philo_args, struct timeval *tm);

void			clean_data(t_philo *philos_arr);

#endif
