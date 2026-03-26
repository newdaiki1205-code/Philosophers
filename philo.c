/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:24:33 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/26 17:59:42 by dshirais         ###   ########.fr       */
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
	print_manager(philo, 'e');
	while (current_time_is() - philo->last_meal < philo->time_to_eat)
	{
		pthread_mutex_lock(philo->access_data);
		if (death_check(philo, 'e'))
		{
			pthread_mutex_unlock(philo->access_data);
			return (1);
		}
		pthread_mutex_unlock(philo->access_data);
		if (philo->time_to_eat - (current_time_is() - philo->last_meal) > 1)
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
	long long	ss;

	print_manager(philo, 's');
	ss = current_time_is();
	while (current_time_is() - ss < philo->time_to_sleep)
	{
		pthread_mutex_lock(philo->access_data);
		if (death_check(philo, 's'))
		{
			pthread_mutex_unlock(philo->access_data);
			return (1);
		}
		pthread_mutex_unlock(philo->access_data);
		if (philo->time_to_sleep - (current_time_is() - ss) > 1)
			usleep(500);
	}
	return (0);
}

// int	thinking(t_philo *philo)
// {
// 	long long	target_time;
// 	long long	think_time;

// 	print_manager(philo, 't');
// 	target_time = philo->last_meal + (philo->time_to_eat * 2);

// 	if(target_time > current_time_is())
// 	{
// 		think_time = 
// 	}

	
// 	ss = current_time_is();
// 	while (current_time_is() - ss < philo->time_to_sleep)
// 	{
// 		pthread_mutex_lock(philo->access_data);
// 		if (death_check(philo, 's'))
// 		{
// 			pthread_mutex_unlock(philo->access_data);
// 			return (1);
// 		}
// 		pthread_mutex_unlock(philo->access_data);
// 		if (philo->time_to_sleep - (current_time_is() - ss) > 1)
// 			usleep(500);
// 	}
// 	return (0);
// }


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
