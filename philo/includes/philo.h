/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabon <acabon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:02:11 by acabon            #+#    #+#             */
/*   Updated: 2025/02/12 18:38:24 by acabon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
// # include <readline/readline.h>
// # include <readline/history.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/time.h>

#include <stdbool.h>

// # include <sys/types.h>
// # include <sys/stat.h>
// # include <fcntl.h>
// # include <unistd.h>
// # include <signal.h>
// # include <sys/wait.h>
// # define ENV 0
// # define PROMPT "minishell:~$ "
// # define FLAGS "\x00\'\""
// # define UNCLOSED_QUOTE 0xffffffffffffffff
// # define NO_ERROR -1
// # define READ 0
// # define WRITE 1
// # define STOP_HEREDOC 0xffffffffffffffff

// typedef int						(*t_func)(char **argv, t_global *global);

typedef struct s_global	t_global;

typedef struct s_philo
{
	pthread_t	id_thread;
	int 		nb;
	unsigned long long			last_eat;
	int			nb_eated;
	t_global	*global;
	// utile ?
	// pthread_mutex_t		fork_left;
	// pthread_mutex_t		fork_right;
}	t_philo;

// typedef struct s_fork
// {
// 	int 		id;
// 	pthread_mutex_t		fork;
// }	t_fork;

typedef struct s_global
{
	int			nb_philos;
	int 		time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_times_must_eat;
	bool		someone_dead;
	unsigned long long	start;
	t_philo		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	available;
	pthread_mutex_t	av_dead_bool;
	pthread_mutex_t	str_out;
}	t_global;



// typedef struct s_builtins
// {
// 	char		*name;
// 	t_func		func;
// }	t_builtins;

// // to delete
// enum	e_flag_value
// {
// 	NO_QUOTE,
// 	SIMPLE_QUOTE,
// 	DOUBLE_QUOTE,
// };

// // FLAG:
// typedef struct s_token
// {
// 	char			*value;
// 	struct s_token	*next;
// 	int				limiter;
// 	t_env			*env;
// }	t_token;


// Utils :
int	ft_isdigit(int c);
int	is_space(int c);
int	is_num(int c);
int	ft_atoi(const char *str);
unsigned long long get_time(void);
void print_lock(t_philo *philo, char *text);




// Routines :
void philo_take_forks(t_philo *philo);
void	philo_eating(t_philo *philo);
void	philo_sleeping(t_philo *philo);
void philo_thinking(t_philo *philo);
void* philo_routine(void* arg);



#endif