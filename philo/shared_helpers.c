/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:00:59 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/15 22:21:21 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_shared_is_dead(t_shared *shared)
{
	int	is_dead;

	pthread_mutex_lock(&shared->is_dead_mtx);
	is_dead = shared->is_dead_soul;
	pthread_mutex_unlock(&shared->is_dead_mtx);
	return (is_dead);
}

void	set_shared_is_dead(t_shared *shared, int is_dead)
{
	pthread_mutex_lock(&shared->is_dead_mtx);
	shared->is_dead_soul = is_dead;
	pthread_mutex_unlock(&shared->is_dead_mtx);
}

int	get_shared_detached(t_shared *shared)
{
	int	detached_ph_nb;

	pthread_mutex_lock(&shared->data_mtx);
	detached_ph_nb = shared->detached_ph_nb;
	pthread_mutex_unlock(&shared->data_mtx);
	return (detached_ph_nb);
}

void	inc_shared_detached(t_shared *shared)
{
	pthread_mutex_lock(&shared->data_mtx);
	shared->detached_ph_nb += 1;
	pthread_mutex_unlock(&shared->data_mtx);
}
