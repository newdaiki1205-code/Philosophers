/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   each_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 16:03:36 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/27 15:46:43 by dshirais         ###   ########.fr       */
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
	pthread_mutex_lock(philo->access_data);
	*philo->death = 1;
	pthread_mutex_unlock(philo->access_data);
}

void	even_philo(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = fork_first(philo);
	second = fork_second(philo);
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat * 1000);
	while (1)
	{
		pthread_mutex_lock(first);
		print_manager(philo, 'f');
		pthread_mutex_lock(second);
		print_manager(philo, 'f');
		if (eating(philo))
			return ;
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		if (meal_count_check(philo))
			return ;
		if (sleeping(philo))
			return ;
		print_manager(philo, 't');
	}
}

void	odd_philo(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = fork_first(philo);
	second = fork_second(philo);
	waiting_list(philo);
	while (1)
	{
		pthread_mutex_lock(first);
		print_manager(philo, 'f');
		pthread_mutex_lock(second);
		print_manager(philo, 'f');
		if (eating(philo))
			return ;
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		if (meal_count_check(philo))
			return ;
		if (sleeping(philo))
			return ;
		if (thinking(philo))
			return ;
	}
}
