/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabon <acabon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:02:11 by acabon            #+#    #+#             */
/*   Updated: 2025/02/14 19:13:51 by acabon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_global	t_global;

typedef struct s_philo
{
	pthread_t			id_thread;
	int					nb;
	unsigned long long	last_eat;
	int					nb_eated;
	t_global			*global;
	int					nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_times_must_eat;
	pthread_mutex_t		fork_left;
	pthread_mutex_t		*fork_right;
	struct s_philo		*next;
}	t_philo;

typedef struct s_global
{
	int					nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_times_must_eat;
	int					nb_finish;
	bool				someone_dead;
	unsigned long long	start;
	t_philo				*philos;
	pthread_mutex_t		av_nb_finish;
	pthread_mutex_t		av_dead_bool;
	pthread_mutex_t		str_out;
}	t_global;

// Utils :
int					ft_isdigit(char *str);
int					ft_atoi(const char *str);
unsigned long long	get_time(void);
void				print_lock(t_philo *philo, char *text);

// Philos :
t_philo				*new_philo(t_global *global, int i);
void				add_back_philo(t_philo **lst, t_philo *new_philo);
int					philo_creation(t_global *global);
void				free_philo(t_global global, int nb_philo);

// Routines :
int					philo_take_forks(t_philo *philo);
int					philo_eating(t_philo *philo);
int					philo_sleeping(t_philo *philo);
int					philo_thinking(t_philo *philo);
void				*philo_routine(void *arg);

// Utils_routines
void				set_as_finish(t_philo *philo);
int					check_dead(t_philo *philo);
int					check_die_in_usleep(t_philo *philo, int time);

#endif