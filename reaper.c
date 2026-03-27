/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:26:57 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/20 20:34:03 by dshirais         ###   ########.fr       */
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
		usleep(100);
		pthread_mutex_lock(&data->philo[i].time_manage);
		if (!(are_you_full(data, i)) && ((current_time - data->start_time)
				- (data->philo[i].last_meal
					- data->start_time) >= data->time_to_die))
		{
			reaper_kill_program(data, i);
			return ;
		}
		pthread_mutex_unlock(&data->philo[i].time_manage);
		if (reaper_eat_check(data))
			return ;
		if (reaper_death_check(data))
			return ;
		i++;
	}
}

int	reaper_eat_check(t_data *data)
{
	pthread_mutex_lock(&data->acess_data);
	if (data->num_of_eat > 0 && (data->total_eat == data->num_of_philo
			* data->num_of_eat))
	{
		pthread_mutex_unlock(&data->acess_data);
		return (1);
	}
	pthread_mutex_unlock(&data->acess_data);
	return (0);
}

int	reaper_death_check(t_data *data)
{
	pthread_mutex_lock(&data->acess_data);
	if (data->death)
	{
		pthread_mutex_unlock(&data->acess_data);
		return (1);
	}
	pthread_mutex_unlock(&data->acess_data);
	return (0);
}

int	are_you_full(t_data *data, int i)
{
	int	re;

	pthread_mutex_lock(&data->acess_data);
	if (data->finish_eat[i])
		re = 1;
	else
		re = 0;
	pthread_mutex_unlock(&data->acess_data);
	return (re);
}
