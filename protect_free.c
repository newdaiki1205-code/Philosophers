/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:26:36 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/20 21:09:15 by dshirais         ###   ########.fr       */
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
	mutex_destroy_philo(data);
	mutex_destroy_data(data);
	if (data->fork)
		free(data->fork);
	if (data->philo)
		free(data->philo);
	if (data->finish_eat)
		free(data->finish_eat);
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
	pthread_mutex_destroy(&data->acess_data);
}

void	mutex_destroy_philo(t_data *data)
{
	int	i;

	if (data->philo)
	{
		i = 0;
		while (i < data->num_of_philo)
		{
			pthread_mutex_destroy(&data->philo[i].time_manage);
			i++;
		}
	}
}
