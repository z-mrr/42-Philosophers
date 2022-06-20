/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:03:24 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/06/20 15:58:58 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int ms)
{
	long	time;

	time = gettime();
	while ((gettime() - time) < ms)
		usleep(ms);
}

void	free_destroy(t_data data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data.n_philos)
		pthread_mutex_destroy(&data.mutex_fork[i]);
	pthread_mutex_destroy(&data.mutex_log);
	free (data.mutex_fork);
	free (philo);
}

void	print_log(t_philo philo, char *log)
{
	pthread_mutex_lock(&philo.data->mutex_log);
	if (!philo.data->stop)
		printf("%ld %d %s\n", gettime() - philo.data->start, philo.id, log);
	pthread_mutex_unlock(&philo.data->mutex_log);
}

long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	ft_atol(const char *nptr)
{
	int		i;
	int		sig;
	long	res;

	i = 0;
	sig = 1;
	res = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sig = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sig);
}
