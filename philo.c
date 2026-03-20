/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:24:33 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/20 20:39:34 by dshirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check(t_philo *philo, char flag)
{
	if (*philo->death)
	{
		if (flag == 'e')
		{
			pthread_mutex_unlock(philo->fork_left);
			pthread_mutex_unlock(philo->fork_right);
		}
		return (1);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	long long	current_time;

	print_manager(philo, 'e');
	current_time = current_time_is();
	while (current_time - philo->last_meal < philo->time_to_eat)
	{
		pthread_mutex_lock(philo->access_data);
		if (death_check(philo, 'e'))
		{
			pthread_mutex_unlock(philo->access_data);
			return (1);
		}
		pthread_mutex_unlock(philo->access_data);
		current_time = current_time_is();
		if (philo->time_to_eat - (current_time - philo->last_meal) > 1)
			usleep(500);
	}
	if (philo->num_of_eat > 0)
	{
		philo->meal_count++;
		pthread_mutex_lock(philo->access_data);
		*philo->total_eat = *philo->total_eat + 1;
		pthread_mutex_unlock(philo->access_data);
	}
	return (0);
}

int	sleeping(t_philo *philo)
{
	long long	ct;
	long long	ss;

	print_manager(philo, 's');
	ss = current_time_is();
	ct = current_time_is();
	while (ct - ss < philo->time_to_sleep)
	{
		pthread_mutex_lock(philo->access_data);
		if (death_check(philo, 's'))
		{
			pthread_mutex_unlock(philo->access_data);
			return (1);
		}
		pthread_mutex_unlock(philo->access_data);
		ct = current_time_is();
		if (philo->time_to_sleep - (ct - ss) > 1)
			usleep(500);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->access_data);
	pthread_mutex_unlock(philo->access_data);
	if (philo->num_of_philo == 1)
		return (solo_philo(philo), NULL);
	else if (philo->num_of_philo % 2 == 0)
		even_philo(philo);
	else
		odd_philo(philo);
	return (NULL);
}
