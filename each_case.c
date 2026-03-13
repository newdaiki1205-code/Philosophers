/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   each_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 16:03:36 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/13 15:22:45 by dshirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	solo_philo(t_philo *philo)
{
	long long	current_time;

	print_manager(philo, 'f');
	current_time = current_time_is();
	while (current_time - philo->start_time < philo->time_to_die)
		current_time = current_time_is();
	print_manager(philo, 'd');
	pthread_mutex_lock(&philo->data->death_check);
	philo->data->death = 1;
	pthread_mutex_unlock(&philo->data->death_check);
}

void	three_philo(t_philo *philo)
{
	if (philo->id == 2)
		usleep(philo->time_to_eat * 500);
	if (philo->id == 3)
		usleep(philo->time_to_eat * 1000);
	while (1)
	{
		pthread_mutex_lock(philo->fork_left);
		print_manager(philo, 'f');
		pthread_mutex_lock(philo->fork_right);
		print_manager(philo, 'f');
		if (eating(philo))
			return ;
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		if (philo->meal_count == philo->num_of_eat)
			return ;
		if (sleeping(philo))
			return ;
		print_manager(philo, 't');
	}
}

void	even_philo(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(5000);
	while (1)
	{
		pthread_mutex_lock(philo->fork_left);
		print_manager(philo, 'f');
		pthread_mutex_lock(philo->fork_right);
		print_manager(philo, 'f');
		if (eating(philo))
			return ;
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		if (philo->meal_count == philo->num_of_eat)
			return ;
		if (sleeping(philo))
			return ;
		print_manager(philo, 't');
	}
}

void	odd_philo(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat * 500);
	if (philo->id == philo->data->num_of_philo)
		usleep(philo->time_to_eat * 1000);
	while (1)
	{
		pthread_mutex_lock(philo->fork_left);
		print_manager(philo, 'f');
		pthread_mutex_lock(philo->fork_right);
		print_manager(philo, 'f');
		if (eating(philo))
			return ;
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		if (philo->meal_count == philo->num_of_eat)
			return ;
		if (sleeping(philo))
			return ;
		print_manager(philo, 't');
	}
}
