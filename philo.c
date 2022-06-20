/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:49:52 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/06/20 11:57:48 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_philo *philo)
{
	int	i;
	int	aux;

	if (philo->data->n_meals)
	{
		i = 0;
		aux = 0;
		while (philo[i].id)
		{
			if (philo[i].meals >= philo->data->n_meals)
				aux++;
		i++;
		}
		if (aux >= philo->data->n_philos)
		{
			philo->data->stop = 1;
			return (0);
		}
	}
	return (1);
}

void	*check_stop(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (check_meals(philo))
	{
		i = 0;
		while (i < philo->data->n_philos)
		{
			if (gettime() - philo[i].last_meal >= philo->data->t_die)
			{
				print_log(philo[i], "died");
				philo->data->stop = 1;
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_fork[philo->l_fork]);
	pthread_mutex_lock(&philo->data->mutex_fork[philo->r_fork]);
	print_log(*philo, "has taken a fork");
	print_log(*philo, "has taken a fork");
	print_log(*philo, "is eating");
	philo->last_meal = gettime();
	usleep(philo->data->t_eat * 1000);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->r_fork]);
	philo->meals++;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->n_philos == 1)
	{
		print_log(*philo, "has taken a fork");
		return (NULL);
	}
	while (!philo->data->stop)
	{
		eating(philo);
		print_log(*philo, "is sleeping");
		usleep(philo->data->t_sleep * 1000);
		print_log(*philo, "is thinking");
	}
	return (NULL);
}

void	philosophers(t_philo *philo)
{
	int			i;
	pthread_t	th;

	i = -1;
	philo->data->start = gettime();
	while (++i < philo->data->n_philos)
	{
		if (pthread_create(&philo[i].th, NULL, &routine, &philo[i]) != 0)
			th_err(3);
	}
	if (pthread_create(&th, NULL, &check_stop, philo) != 0)
		th_err(3);
	i = -1;
	while (++i < philo->data->n_philos)
	{
		if (pthread_join(philo[i].th, NULL) != 0)
			th_err(4);
	}
	if (pthread_join(th, NULL) != 0)
		th_err(4);
}
