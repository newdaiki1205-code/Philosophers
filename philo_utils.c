/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 21:07:24 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/30 16:22:09 by dshirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time_is(void)
{
	struct timeval	current_time;
	long long		re;

	gettimeofday(&current_time, NULL);
	re = (long long)current_time.tv_sec * 1000 + (current_time.tv_usec / 1000);
	return (re);
}

void	reaper_kill_program(t_data *data, int i)
{
	print_manager(&data->philo[i], 'd');
	pthread_mutex_lock(&data->acess_data);
	data->death = 1;
	pthread_mutex_unlock(&data->acess_data);
	pthread_mutex_unlock(&data->philo[i].time_manage);
}

pthread_mutex_t	*fork_first(t_philo *philo)
{
	if (philo->fork_left < philo->fork_right)
		return (philo->fork_left);
	else
		return (philo->fork_right);
}

pthread_mutex_t	*fork_second(t_philo *philo)
{
	if (philo->fork_left < philo->fork_right)
		return (philo->fork_right);
	else
		return (philo->fork_left);
}

int	meal_count_check(t_philo *philo)
{
	if (philo->meal_count == philo->num_of_eat)
	{
		pthread_mutex_lock(philo->access_data);
		*philo->finish_eat = 1;
		pthread_mutex_unlock(philo->access_data);
		return (1);
	}
	return (0);
}
