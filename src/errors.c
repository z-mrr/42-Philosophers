/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 17:49:23 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/06/20 12:53:57 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	argn_err(void)
{
	printf("Invalid number of arguments.\n");
	return (1);
}

int	args_err(void)
{
	printf("Invalid arguments.\n");
	return (2);
}

int	th_err(int err)
{
	if (err == 3)
	{
		printf("Failed to create thread.\n");
		return (3);
	}
	else if (err == 4)
	{
		printf("Failed to join thread.\n");
		return (4);
	}
	return (0);
}

int	mem_err(void)
{
	printf("Memory allocation failed.\n");
	return (5);
}
