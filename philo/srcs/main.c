/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabon <acabon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:58:12 by cbeaufil          #+#    #+#             */
/*   Updated: 2025/02/12 18:38:35 by acabon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


// faire une double liste chaine pour eviter les dataraces ?

t_global	init_data(int argc, char **argv)
{
	t_global	global;
	int			i;

	i = 1;
	while (i < argc)
	{
		if (ft_isdigit(ft_atoi(argv[i])))
		{
			global.nb_philos = 0;
			return (global);
			// return ((t_global){0, 0, 0, 0, -1, NULL, NULL, NULL, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER});
		}
		i++;
	}
	pthread_mutex_init(&(global.str_out), NULL);
	global.someone_dead = 0;
	pthread_mutex_init(&(global.av_dead_bool), NULL);
	global.start = get_time();

	printf("test = %llu\n", global.start);


	global.nb_philos =  ft_atoi(argv[1]);
	global.time_to_die =  ft_atoi(argv[2]);
	global.time_to_eat =  ft_atoi(argv[3]);
	global.time_to_sleep =  ft_atoi(argv[4]);
	if (argc > 5)
		global.nb_times_must_eat =  ft_atoi(argv[5]);
	else
		global.nb_times_must_eat =  -1;
	global.philos = malloc(global.nb_philos * sizeof(t_philo));
	global.forks = malloc(global.nb_philos * sizeof(pthread_mutex_t));
	pthread_mutex_init(&(global.available), NULL);


	return (global);
}

int philo_creation(t_global *global)
{
	int i;

	i = 0;
	while (i < global->nb_philos)
	{
		pthread_mutex_init(&(global->forks[i]), NULL);
		global->philos[i].global = global;
		global->philos[i].nb = i + 1;
		global->philos[i].nb_eated = 0;
		// pthread_mutex_init(&(global->philos[i].fork_left), NULL);
		// pthread_mutex_init(&(global->philos[i].fork_right), NULL);
        if (pthread_create(&(global->philos[i].id_thread), NULL, philo_routine, &(global->philos[i])) != 0)
		{
            printf("Erreur lors de la création du thread %d\n", i + 1);
            return (EXIT_FAILURE);
        }
		i++;
    }
	return (EXIT_SUCCESS);
}

void	wait_philo(t_global global)
{
	int i;

	i = 0;
	// printf("gfds = %d\n", global.nb_philos);
	while (i < global.nb_philos)
	{
		pthread_join(global.philos[i].id_thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	// (void)argc;
	// (void)argv;
	t_global	global;

	if (argc < 5 || argc > 6)
	{
		printf("Error: 4 or 5 arguments expected\n");
		return (EXIT_FAILURE);
	}
	global = init_data(argc, argv);
	if (global.nb_philos < 2)
		return (EXIT_SUCCESS);
	if (philo_creation(&global))
		return (EXIT_SUCCESS);
	


	wait_philo(global);
	// int i = 0;
	// printf("gfds = %d\n", global.nb_philos);
	// while (i < global.nb_philos)
	// {
		// pthread_join(global.philos[i].id_thread, NULL);
		// free(global.philos->thread);
		// i++;
	// }
	
	free(global.philos);
	free(global.forks);

	return (EXIT_SUCCESS);
}
