/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:22:26 by tklimova          #+#    #+#             */
/*   Updated: 2024/01/02 16:11:53 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_int_positive_number(char *str)
{
	long	nb;
	int		not_a_nb;

	nb = 0;
	not_a_nb = 0;
	if (str && *str && *str == '+')
		str++;
	while (*str && !not_a_nb)
	{
		if (*str - '0' <= 9 && *str - '0' >= 0)
			nb = nb * 10 + (*str - '0');
		else
			not_a_nb = -2;
		if (nb > INT_MAX)
			not_a_nb = -3;
		str++;
	}
	if (not_a_nb)
		return (not_a_nb);
	return ((int)nb);
}

static void	log_error(int err_no)
{
	if (err_no >= 0)
		return ;
	if (err_no == -1)
		printf("%s", "Incorrect number of arguments: \
			function should be launched with from 3 to 4 arguments");
	else if (err_no == -2)
		printf("%s %i", "Incorrect arguments: \
			all arguments should be positive integer numbers", err_no);
	else if (err_no == -3)
		printf("%s", "Incorrect arguments: \
			arguments bigger than max integer size");
}

static int	is_valid_args(int argc)
{
	int	err_no;

	err_no = 0;
	if (argc < 5 || argc > 6)
	{
		err_no = -1;
		log_error(err_no);
		return (err_no);
	}
	return (0);
}

static void	fill_struct_field(int argc, char **argv, int *args, int *err_no)
{
	int	nb;
	int	i;

	i = 0;
	while (i < argc - 1 && !(*err_no))
	{
		nb = is_int_positive_number(argv[i + 1]);
		if (nb < 0)
		{
			*err_no = nb;
			log_error(nb);
			break ;
		}
		else if (nb >= 0)
			args[i] = nb;
		i++;
	}
}

int	parse_args(t_philo_args *ph_args, int argc, char **argv)
{
	int	err_no;
	int	*args;

	err_no = 0;
	args = malloc(sizeof(int) * 5);
	err_no = is_valid_args(argc);
	fill_struct_field(argc, argv, args, &err_no);
	ph_args->number_of_philosophers = args[0];
	ph_args->time_to_die = args[1];
	ph_args->time_to_eat = args[2];
	ph_args->time_to_sleep = args[3];
	if (argc > 5)
	{
		ph_args->have_oblig = 1;
		ph_args->number_of_times_each_philosopher_must_eat = args[4];
	}
	free(args);
	return (err_no);
}
