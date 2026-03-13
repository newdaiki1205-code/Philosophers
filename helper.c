/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:23:01 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/13 15:29:49 by dshirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;

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
		nptr++;
	}
	return (res * sign);
}

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
	pthread_mutex_lock(&data->death_check);
	data->death = 1;
	pthread_mutex_unlock(&data->death_check);
	print_manager(&data->philo[i], 'd');
	reaper_mutex_unlock(data, &data->philo[i]);
}
