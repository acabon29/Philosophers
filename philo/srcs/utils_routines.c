/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabon <acabon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:23:26 by acabon            #+#    #+#             */
/*   Updated: 2025/02/14 19:17:09 by acabon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_as_finish(t_philo *philo)
{
	pthread_mutex_lock(&(philo->global->av_nb_finish));
	philo->global->nb_finish++;
	pthread_mutex_unlock(&(philo->global->av_nb_finish));
}

int	is_finish(t_global *global)
{
	pthread_mutex_lock(&(global->av_nb_finish));
	if (global->nb_finish == global->nb_philos)
	{
		pthread_mutex_unlock(&(global->av_nb_finish));
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&(global->av_nb_finish));
	return (EXIT_SUCCESS);
}

int	check_this_dead(t_philo *philo)
{
	if ((philo->last_eat + philo->time_to_die) <= get_time())
	{
		print_lock(philo, "is dead");
		philo->global->someone_dead = true;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_dead(t_philo *philo)
{
	if (is_finish(philo->global))
		return (EXIT_FAILURE);
	pthread_mutex_lock(&(philo->global->av_dead_bool));
	if (philo->global->someone_dead == true)
	{
		pthread_mutex_unlock(&(philo->global->av_dead_bool));
		return (EXIT_FAILURE);
	}
	if (check_this_dead(philo))
	{
		pthread_mutex_unlock(&(philo->global->av_dead_bool));
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&(philo->global->av_dead_bool));
	return (EXIT_SUCCESS);
}

int	check_die_in_usleep(t_philo *philo, int time)
{
	long long	will_die;

	will_die = (get_time() + time)
		- (philo->last_eat + philo->time_to_die);
	if (will_die >= 0)
	{
		usleep(((long long)(philo->last_eat + philo->time_to_die)
				- get_time()) * 1000);
		check_dead(philo);
		pthread_mutex_unlock(&(philo->fork_left));
		return (pthread_mutex_unlock(philo->fork_right),
			EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
