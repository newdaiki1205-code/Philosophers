/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 16:06:06 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/20 19:12:59 by dshirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_manager(t_philo *philo, char flag)
{
	long long	timestamp;

	timestamp = current_time_is();
	if (flag == 'e')
	{
		pthread_mutex_lock(&philo->time_manage);
		philo->last_meal = timestamp;
		pthread_mutex_unlock(&philo->time_manage);
	}
	pthread_mutex_lock(philo->access_data);
	if (flag == 'f')
		print_taken_fork(philo, timestamp);
	else if (flag == 'e')
		print_is_eating(philo);
	else if (flag == 's')
		print_is_sleeping(philo, timestamp);
	else if (flag == 't')
		print_is_thinking(philo, timestamp);
	else if (flag == 'd')
		print_died(philo, timestamp);
	pthread_mutex_unlock(philo->access_data);
}
