/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 02:47:39 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/03 03:51:39 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*eat()
{
	// pthread_mutex_lock();
	printf("%s\n", "Philo eats");
	// pthread_mutex_unlock();
	return (NULL);
}
