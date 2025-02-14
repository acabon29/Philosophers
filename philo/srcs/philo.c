/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabon <acabon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:54:38 by acabon            #+#    #+#             */
/*   Updated: 2025/02/14 19:02:48 by acabon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*new_philo(t_global *global, int i)
{
	t_philo	*new_philo;

	new_philo = (t_philo *)malloc(sizeof(t_philo));
	if (new_philo == NULL)
		return (NULL);
	new_philo->global = global;
	new_philo->nb = i + 1;
	new_philo->nb_eated = 0;
	new_philo->nb_philos = global->nb_philos;
	new_philo->time_to_die = global->time_to_die;
	new_philo->time_to_eat = global->time_to_eat;
	new_philo->time_to_sleep = global->time_to_sleep;
	new_philo->nb_times_must_eat = global->nb_times_must_eat;
	pthread_mutex_init(&(new_philo->fork_left), NULL);
	new_philo->next = NULL;
	return (new_philo);
}

void	add_back_philo(t_philo **lst, t_philo *new_philo)
{
	t_philo	*current_list;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new_philo;
	else
	{
		current_list = *lst;
		while (current_list != NULL)
		{
			if (current_list->next == NULL)
			{
				current_list->next = new_philo;
				return ;
			}
			current_list = current_list->next;
		}
	}
}

int	create_thread(t_global global, t_philo *current_philo,
	t_philo *other_philo, int nb)
{
	current_philo->fork_right = &(other_philo->fork_left);
	if (pthread_create(&(current_philo->id_thread),
			NULL, philo_routine, current_philo) != 0)
	{
		free_philo(global, nb);
		printf("Erreur lors de la création du thread %d\n", nb);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	philo_creation(t_global *global)
{
	t_philo	*current_philo;
	t_philo	*pre_philo;
	int		i;

	i = 0;
	global->philos = NULL;
	while (i < global->nb_philos)
	{
		current_philo = new_philo(global, i);
		if (current_philo == NULL)
		{
			free_philo(*global, i);
			return (EXIT_FAILURE);
		}
		add_back_philo(&(global->philos), current_philo);
		if (i != 0)
			if (create_thread (*global, pre_philo, current_philo, i + 1))
				return (EXIT_FAILURE);
		pre_philo = current_philo;
		i++;
	}
	current_philo->next = global->philos;
	if (create_thread (*global, current_philo, global->philos, i + 1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// printf("philo %d has eaten %d\n", current->nb, current->nb_eated);
void	free_philo(t_global global, int nb_philo)
{
	t_philo	*current;
	t_philo	*prev;
	int		i;

	i = 0;
	current = global.philos;
	while (i < nb_philo)
	{
		prev = current;
		current = current->next;
		free(prev);
		i++;
	}
}
