/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:17:38 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/06/20 15:59:17 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_data
{
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	long			start;
	int				stop;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_log;
}				t_data;

typedef struct s_philo
{
	int			id;
	int			meals;
	long		last_meal;
	int			l_fork;
	int			r_fork;
	t_data		*data;
	pthread_t	th;
}				t_philo;

//main.c
int		init_data(t_data *data, int ac, char **av);
int		init_philo(t_data *data, t_philo **philo);
int		check_args(char **av);

//philo.c
int		has_eaten(t_philo *philo);
void	*check_stop(void *arg);
void	is_eating(t_philo *philo);
void	*routine(void *philo);
void	philosophers(t_philo *philo);

//utils.c
void	ft_usleep(int ms);
void	free_destroy(t_data data, t_philo *philo);
void	print_log(t_philo philo, char *log);
long	gettime(void);
long	ft_atol(const char *nptr);

//errors.c
int		argn_err(void);
int		args_err(void);
int		th_err(int err);
int		mem_err(void);

#endif
