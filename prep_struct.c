/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:25:36 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/20 21:08:58 by dshirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	prep_data(t_data *data, char **av)
{
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	how_many_times(data, av);
	data->fork = (pthread_mutex_t *)malloc(data->num_of_philo
			* sizeof(pthread_mutex_t));
	if (!data->fork)
		return (1);
	data->death = 0;
	data->philo = (t_philo *)malloc(data->num_of_philo * sizeof(t_philo));
	if (!data->philo)
		return (1);
	mutex_init_data(data);
	data->start_time = current_time_is();
	data->finish_eat = (int *)malloc(data->num_of_philo * sizeof(int));
	if (!data->finish_eat)
		return (1);
	memset(data->finish_eat, 0, data->num_of_philo * sizeof(int));
	return (0);
}

void	mutex_init_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->acess_data, NULL);
}

void	how_many_times(t_data *data, char **av)
{
	if (av[5])
	{
		data->num_of_eat = ft_atoi(av[5]);
		data->total_eat = 0;
	}
	else
	{
		data->num_of_eat = -1;
		data->total_eat = -1;
	}
}

int	prep_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].fork_left = &data->fork[i];
		if (i == 0)
			data->philo[i].fork_right = &data->fork[data->num_of_philo - 1];
		else
			data->philo[i].fork_right = &data->fork[i - 1];
		philo_init(data, i);
		i++;
	}
	return (0);
}

void	philo_init(t_data *data, int i)
{
	pthread_mutex_init(&data->philo[i].time_manage, NULL);
	data->philo[i].access_data = &data->acess_data;
	data->philo[i].num_of_philo = data->num_of_philo;
	data->philo[i].time_to_die = data->time_to_die;
	data->philo[i].time_to_eat = data->time_to_eat;
	data->philo[i].time_to_sleep = data->time_to_sleep;
	data->philo[i].num_of_eat = data->num_of_eat;
	data->philo[i].meal_count = 0;
	data->philo[i].start_time = data->start_time;
	data->philo[i].last_meal = data->start_time;
	data->philo[i].death = &data->death;
	data->philo[i].total_eat = &data->total_eat;
	data->philo[i].finish_eat = &data->finish_eat[i];
}
