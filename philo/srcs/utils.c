/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabon <acabon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:38:26 by acabon            #+#    #+#             */
/*   Updated: 2025/02/12 18:24:36 by acabon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_space(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	is_num(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int	nb;
	int	signe;

	nb = 0;
	signe = 1;
	while (*str && is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -signe;
		str++;
	}
	while (is_num(*str))
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return (nb * signe);
}

unsigned long long get_time(void)
{
	unsigned long long res;
	struct timeval time;

	gettimeofday(&time, NULL);
	res = (time.tv_sec * 1000 + (time.tv_usec / 1000));
	return (res);
}


void print_lock(t_philo *philo, char *text)
{
	unsigned long long time;
	t_global	*global;
	int	id_philo;

	id_philo = philo->nb;
	global = philo->global;
	pthread_mutex_lock(&(global->str_out));
	time = get_time() - global->start;
	printf("%llu %d %s\n", time, id_philo, text); // Ajouter le temps
	// printf("test %d is sleeping\n", id_philo); // Ajouter le temps
	pthread_mutex_unlock(&(global->str_out));
}