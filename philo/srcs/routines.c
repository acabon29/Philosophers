/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabon <acabon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:33:53 by acabon            #+#    #+#             */
/*   Updated: 2025/02/14 19:16:23 by acabon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_take_forks(t_philo *philo)
{
	if (check_dead(philo))
		return (EXIT_FAILURE);
	pthread_mutex_lock(&(philo->fork_left));
	if (check_dead(philo))
	{
		pthread_mutex_unlock(&(philo->fork_left));
		return (EXIT_FAILURE);
	}
	print_lock(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_right);
	if (check_dead(philo))
	{
		pthread_mutex_unlock(&(philo->fork_left));
		return (EXIT_FAILURE);
	}
	print_lock(philo, "has taken a fork");
	return (EXIT_SUCCESS);
}

int	philo_eating(t_philo *philo)
{
	if (check_dead(philo))
	{
		pthread_mutex_unlock(&(philo->fork_left));
		return (pthread_mutex_unlock(philo->fork_right), EXIT_FAILURE);
	}
	print_lock(philo, "is eating");
	if (check_die_in_usleep(philo, philo->time_to_eat))
	{
		pthread_mutex_unlock(&(philo->fork_left));
		pthread_mutex_unlock(philo->fork_right);
		return (pthread_mutex_unlock(philo->fork_right), EXIT_FAILURE);
	}
	usleep(philo->time_to_eat * 1000);
	philo->last_eat = get_time();
	if (check_dead(philo))
	{
		pthread_mutex_unlock(&(philo->fork_left));
		pthread_mutex_unlock(philo->fork_right);
		return (pthread_mutex_unlock(philo->fork_right), EXIT_FAILURE);
	}
	pthread_mutex_unlock(&(philo->fork_left));
	pthread_mutex_unlock(philo->fork_right);
	if (check_dead(philo))
		return (EXIT_FAILURE);
	return (philo->nb_eated++, EXIT_SUCCESS);
}

int	philo_sleeping(t_philo *philo)
{
	if (check_dead(philo))
		return (EXIT_FAILURE);
	print_lock(philo, "is sleeping");
	if (check_die_in_usleep(philo, philo->time_to_sleep))
		return (pthread_mutex_unlock(philo->fork_right), EXIT_FAILURE);
	usleep(philo->time_to_sleep * 1000);
	if (check_dead(philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	philo_thinking(t_philo *philo)
{
	if (check_dead(philo))
		return (EXIT_FAILURE);
	print_lock(philo, "is thinking");
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_eat = get_time();
	while (1)
	{
		if (philo->nb_eated == 0 && philo->nb % 2 == 0)
		{
			usleep(100);
			if (philo_thinking(philo))
				return (NULL);
		}
		if (philo_take_forks(philo))
			return (NULL);
		if (philo_eating(philo))
			return (NULL);
		if (philo->nb_eated == philo->nb_times_must_eat)
			set_as_finish(philo);
		if (philo_sleeping(philo))
			return (NULL);
		if (philo_thinking(philo))
			return (NULL);
	}
	return (NULL);
}
