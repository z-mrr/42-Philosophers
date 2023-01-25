/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:53:44 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/06/21 18:18:06 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int ac, char **av)
{
	data->n_philos = ft_atol(av[1]);
	data->t_die = ft_atol(av[2]);
	data->t_eat = ft_atol(av[3]);
	data->t_sleep = ft_atol(av[4]);
	data->n_meals = 0;
	if (ac == 6)
		data->n_meals = ft_atol(av[5]);
	data->stop = 0;
	data->mutex_fork = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->mutex_fork)
		return (1);
	pthread_mutex_init(&data->mutex_log, NULL);
	return (0);
}

int	init_philo(t_data *data, t_philo **philo)
{
	int		i;
	t_philo	*aux;

	aux = malloc(sizeof(t_data) * data->n_philos);
	if (!aux)
		return (1);
	i = -1;
	while (++i < data->n_philos)
	{
		aux[i].id = i + 1;
		aux[i].meals = 0;
		aux[i].l_fork = i;
		aux[i].r_fork = i + 1;
		aux[i].data = data;
		pthread_mutex_init(&data->mutex_fork[i], NULL);
	}
	i--;
	aux[i].r_fork = 0;
	*philo = aux;
	return (0);
}

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9'
				|| ft_atol(av[i]) == 0
				|| ft_atol(av[i]) > 2147483647)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (ac < 5 || ac > 6)
		return (argn_err());
	if (!check_args(av))
		return (args_err());
	if (init_data(&data, ac, av) || init_philo(&data, &philo))
		return (mem_err());
	philosophers(philo);
	free_destroy(data, philo);
	return (0);
}
