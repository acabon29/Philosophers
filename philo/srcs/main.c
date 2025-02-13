/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabon <acabon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:58:12 by cbeaufil          #+#    #+#             */
/*   Updated: 2025/02/13 20:02:30 by acabon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// pas en dessous de 60ms pour tout et au dessus de 200 philo
int	check_args(int argc, char **argv)
{
	int	i;
	int	nb;

	i = 1;
	while (i < argc)
	{
		nb = ft_atoi(argv[i]);
		if (ft_isdigit(argv[i]))
			return (EXIT_FAILURE);
		if (i == 1 && nb > 200)
			return (EXIT_FAILURE);
		if (i > 1 && i != 5 && nb < 60)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

t_global	init_data(int argc, char **argv)
{
	t_global	global;

	if (check_args(argc, argv))
	{
		printf("Error: invalid argument\n");
		global.nb_philos = 0;
		return (global);
	}
	pthread_mutex_init(&(global.str_out), NULL);
	global.someone_dead = false;
	pthread_mutex_init(&(global.av_dead_bool), NULL);
	global.start = get_time();
	global.nb_philos = ft_atoi(argv[1]);
	global.time_to_die = ft_atoi(argv[2]);
	global.time_to_eat = ft_atoi(argv[3]);
	global.time_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		global.nb_times_must_eat = ft_atoi(argv[5]);
	else
		global.nb_times_must_eat = -1;
	return (global);
}

void	wait_philo(t_global global)
{
	t_philo	*current_philo;
	int		i;

	i = 0;
	current_philo = global.philos;
	while (i < global.nb_philos)
	{
		pthread_join(current_philo->id_thread, NULL);
		current_philo = current_philo->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_global	global;

	if (5 > argc || argc > 6)
	{
		printf("Error: 4 or 5 arguments expected\n");
		return (EXIT_FAILURE);
	}
	global = init_data(argc, argv);
	if (global.nb_philos < 1)
		return (EXIT_SUCCESS);
	if (global.nb_philos == 1)
	{
		printf("0 1 is dead\n");
		return (EXIT_SUCCESS);
	}
	if (philo_creation(&global))
		return (EXIT_SUCCESS);
	wait_philo(global);
	free_philo(global, global.nb_philos);
	return (EXIT_SUCCESS);
}
