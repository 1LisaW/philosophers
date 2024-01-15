/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 07:27:20 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/14 23:56:54 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_print_main_info(t_philo *ph, struct timeval *timestamp,
			char *text, enum e_philo_states state)
{
	if (state == eating)
		printf("\n%li (%li from last meal) %i %s (%i times)\n",
			get_ms_diff(&ph->timestemp_create, timestamp),
			get_ms_diff(&ph->timestemp_eaten, timestamp), ph->nb,
			text, ph->has_eaten + 1);
	else
		printf("\n%li (%li from last meal) %i %s\n",
			get_ms_diff(&ph->timestemp_create, timestamp),
			get_ms_diff(&ph->timestemp_eaten, timestamp), ph->nb, text);
}

static void	ft_print_fork_info(t_philo *ph, struct timeval *timestamp,
			char *text, int fork_idx)
{
	if (fork_idx == 1)
		printf("\n%li (%li from last meal) %i %s (%p)\n",
			get_ms_diff(&ph->timestemp_create, timestamp),
			get_ms_diff(&ph->timestemp_eaten, timestamp), ph->nb,
			text, ph->fork_l);
	else if (fork_idx == 2)
		printf("\n%li (%li from last meal) %i %s (%p)\n",
			get_ms_diff(&ph->timestemp_create, timestamp),
			get_ms_diff(&ph->timestemp_eaten, timestamp), ph->nb,
			text, ph->fork_r);
}

void	ft_print_info(t_philo *ph, struct timeval *timestamp,
			enum e_philo_states state, int fork_idx)
{
	if ((state == thinking) && !fork_idx)
		ft_print_main_info(ph, timestamp, "is thinking", thinking);
	else if (state == thinking && fork_idx == 1)
		ft_print_fork_info(ph, timestamp, "is taking left fork", 1);
	else if (state == thinking && fork_idx == 2)
		ft_print_fork_info(ph, timestamp, "is taking right fork", 2);
	else if (state == sleeping)
	{
		ft_print_main_info(ph, timestamp, "is sleeping", sleeping);
	}
	else if (state == eating && fork_idx)
	{
		ft_print_fork_info(ph, timestamp, "is dropping left fork", 1);
		ft_print_fork_info(ph, timestamp, "is dropping right fork", 2);
	}
	else if (state == eating)
		ft_print_main_info(ph, timestamp, "is eating", eating);
	else if (state == dead)
		ft_print_main_info(ph, timestamp, "is dead", dead);
}
