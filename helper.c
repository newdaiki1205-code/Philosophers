/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:23:01 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/27 15:48:12 by dshirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoll(const char *nptr)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - '0');
		if (res > 2147483647 || res < -2147483648)
			return (-1);
		nptr++;
	}
	return (res * sign);
}

void	waiting_list(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat * 500);
	if (philo->id == philo->num_of_philo)
		usleep(philo->time_to_eat * 1000);
}

int	smart_sleep(t_philo *philo, long long start_time, char flag,
		long long wait_time)
{
	while (current_time_is() - start_time < wait_time)
	{
		pthread_mutex_lock(philo->access_data);
		if (death_check(philo, flag))
		{
			pthread_mutex_unlock(philo->access_data);
			return (1);
		}
		pthread_mutex_unlock(philo->access_data);
		if ((wait_time - (current_time_is() - start_time) > 1))
			usleep(500);
	}
	return (0);
}
