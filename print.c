/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:26:03 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/12 16:06:40 by dshirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_taken_fork(t_philo *philo, long long timestamp)
{
	if (death_check(philo, 'p'))
		return ;
	printf("%lld Philosopher %d has taken a fork\n", timestamp
		- philo->start_time, philo->id);
}

void	print_is_eating(t_philo *philo)
{
	if (death_check(philo, 'p'))
		return ;
	printf("%lld Philosopher %d is eating\n", philo->last_meal
		- philo->start_time, philo->id);
}

void	print_is_sleeping(t_philo *philo, long long timestamp)
{
	if (death_check(philo, 'p'))
		return ;
	printf("%lld Philosopher %d is sleeping\n", timestamp - philo->start_time,
		philo->id);
}

void	print_is_thinking(t_philo *philo, long long timestamp)
{
	if (death_check(philo, 'p'))
		return ;
	printf("%lld Philosopher %d is thinking\n", timestamp - philo->start_time,
		philo->id);
}

void	print_died(t_philo *philo, long long timestamp)
{
	if (death_check(philo, 'p'))
		return ;
	printf("%lld Philosopher %d died\n", timestamp - philo->start_time,
		philo->id);
}
