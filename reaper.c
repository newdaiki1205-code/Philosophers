/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:26:57 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/09 15:05:29 by dshirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	are_you_alive(t_data *data)
{
	int			i;
	long long	current_time;

	i = 0;
	while (1)
	{
		if (i == data->num_of_philo)
			i = 0;
		current_time = current_time_is();
		usleep(1000);
		reaper_mutex_lock(data, &data->philo[i]);
		if ((data->philo[i].meal_count != data->num_of_eat) && ((current_time
					- data->start_time) - (data->philo[i].last_meal
					- data->start_time) >= data->time_to_die))
		{
			reaper_kill_program(data, i);
			return ;
		}
		reaper_mutex_unlock(data, &data->philo[i]);
		if (reaper_eat_check(data))
			return ;
		if (reaper_death_check(data))
			return ;
		i++;
	}
}

void	reaper_mutex_lock(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->time_manage);
	pthread_mutex_lock(&philo->lock_meal_count);
	pthread_mutex_lock(&data->eat_count);
}

void	reaper_mutex_unlock(t_data *data, t_philo *philo)
{
	pthread_mutex_unlock(&philo->time_manage);
	pthread_mutex_unlock(&philo->lock_meal_count);
	pthread_mutex_unlock(&data->eat_count);
}

int	reaper_eat_check(t_data *data)
{
	pthread_mutex_lock(&data->eat_count);
	if (data->num_of_eat > 0 && (data->total_eat == data->num_of_philo
			* data->num_of_eat))
	{
		pthread_mutex_unlock(&data->eat_count);
		return (1);
	}
	pthread_mutex_unlock(&data->eat_count);
	return (0);
}

int	reaper_death_check(t_data *data)
{
	pthread_mutex_lock(&data->death_check);
	if (data->death)
	{
		pthread_mutex_unlock(&data->death_check);
		return (1);
	}
	pthread_mutex_unlock(&data->death_check);
	return (0);
}
