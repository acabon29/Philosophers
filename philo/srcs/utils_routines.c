/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabon <acabon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:23:26 by acabon            #+#    #+#             */
/*   Updated: 2025/02/13 19:29:24 by acabon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	someone_dead(t_global *global)
{
	if (global->someone_dead == true)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->global->av_dead_bool));
	if (someone_dead(philo->global))
	{
		pthread_mutex_unlock(&(philo->global->av_dead_bool));
		return (EXIT_FAILURE);
	}
	if ((philo->last_eat + philo->time_to_die) <= get_time())
	{
		print_lock(philo, "is dead");
		philo->global->someone_dead = true;
		pthread_mutex_unlock(&(philo->global->av_dead_bool));
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&(philo->global->av_dead_bool));
	return (EXIT_SUCCESS);
}
