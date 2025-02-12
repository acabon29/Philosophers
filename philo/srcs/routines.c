/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabon <acabon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:33:53 by acabon            #+#    #+#             */
/*   Updated: 2025/02/12 18:34:46 by acabon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void philo_take_forks(t_philo *philo)
{
	int	id_philo;
	t_global	*global;
	// unsigned long long time;
	// int nb_philos;

	id_philo = philo->nb;
	global = philo->global;

	// pthread_mutex_lock(&(global->available));
	pthread_mutex_lock(&(global->forks[id_philo - 1]));
	// pthread_mutex_unlock(&(global->available));

	// verrifier si la personne est morte
	// pthread_mutex_lock(&(global->str_out));
	// time = get_time() - global->start;
	// printf("%llu %d has taken a fork\n", time, id_philo); // Ajouter le temps
	// pthread_mutex_unlock(&(global->str_out));
	print_lock(philo, "has taken a fork");


	// pthread_mutex_lock(&(philo->fork_left));
	
	// pthread_mutex_lock(&(global->available));
	pthread_mutex_lock(&(global->forks[(id_philo) % global->nb_philos]));
	// pthread_mutex_unlock(&(global->available));
	// verrifier si la personne est morte
	// pthread_mutex_lock(&(global->str_out));
	// time = get_time() - global->start;
	// printf("%llu %d has taken a fork\n", time, id_philo); // Ajouter le temps
	// pthread_mutex_unlock(&(global->str_out));
	print_lock(philo, "has taken a fork");


	// pthread_mutex_lock(&(philo->fork_right));
}


void	philo_eating(t_philo *philo)
{
	t_global	*global;
	int	id_philo;
	// unsigned long long time;

	// printf("test\n"); // Ajouter le temps

	id_philo = philo->nb;
	global = philo->global;
	// pthread_mutex_lock(&(philo->fork_right));
	// pthread_mutex_lock(&(philo->fork_left));

	// pthread_mutex_lock(&(global->str_out));
	// time = get_time() - global->start;
	// printf("%llu %d is eating\n", time, id_philo); // Ajouter le temps
	// pthread_mutex_unlock(&(global->str_out));

	print_lock(philo, "is eating");

	usleep(global->time_to_eat * 1000);


	// pthread_mutex_unlock(&(philo->fork_right));
	// pthread_mutex_unlock(&(philo->fork_left));

	// pthread_mutex_lock(&(global->available));
	pthread_mutex_unlock(&(global->forks[id_philo - 1]));
	pthread_mutex_unlock(&(global->forks[(id_philo) % global->nb_philos]));
	// pthread_mutex_unlock(&(global->available));



	// ajuster la derniere fois qu'il a mange
	// philo->last_eat = 
	philo->nb_eated++; 

}


void	philo_sleeping(t_philo *philo)
{
	// unsigned long long time;
	// t_global	*global;
	// int	id_philo;

	// id_philo = philo->nb;
	// global = philo->global;
	// pthread_mutex_lock(&(global->str_out));
	// time = get_time() - global->start;
	// printf("%llu %d is sleeping\n", time, id_philo); // Ajouter le temps
	print_lock(philo, "is sleeping");
	// printf("test %d is sleeping\n", id_philo); // Ajouter le temps
	// pthread_mutex_unlock(&(global->str_out));
	usleep(philo->global->time_to_sleep);
}

void philo_thinking(t_philo *philo)
{
	// t_global	*global;
	// int	id_philo;
	// // unsigned long long time;

	// id_philo = philo->nb;
	// global = philo->global;
	// pthread_mutex_lock(&(global->str_out));
	// time = get_time() - global->start;
	// printf("%llu %d is thinking\n", time, id_philo); // Ajouter le temps
	// pthread_mutex_unlock(&(global->str_out));
	print_lock(philo, "is thinking");

	// usleep(100);
}




void* philo_routine(void* arg)
{
	(void)arg;
	t_philo	*philo;

	philo = (t_philo*)arg;


	// a supp :
	// printf("philo_routine %lu\n", philo->id_thread);

// 	initialiser ici le "last_eat"


	while (1)
	{
		if (philo->nb_eated == 0 && philo->nb % 2 == 0)
			philo_thinking(philo);
		philo_take_forks(philo);
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
		if (philo->nb_eated == philo->global->time_to_eat)
			break;
	}


    return(NULL);
}

