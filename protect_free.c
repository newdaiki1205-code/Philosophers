/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:26:36 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/13 15:03:22 by dshirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input_check(int ac, char **av)
{
	int	i;
	int	num;

	i = 1;
	while (i < ac)
	{
		num = ft_atoi(av[i]);
		if (num < 1)
			return (1);
		i++;
	}
	return (0);
}

void	free_all(t_data *data)
{
	mutex_destroy_data(data);
	if (data->fork)
		free(data->fork);
	if (data->philo)
		free(data->philo);
	if (data)
		free(data);
}

void	mutex_destroy_data(t_data *data)
{
	int	i;

	if (data->fork)
	{
		i = 0;
		while (i < data->num_of_philo)
		{
			pthread_mutex_destroy(&data->fork[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&data->death_check);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->eat_count);
	pthread_mutex_destroy(&data->lock_routine);
}
