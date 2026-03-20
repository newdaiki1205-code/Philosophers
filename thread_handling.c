/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:27:31 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/20 18:45:18 by dshirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	prep_thread(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->acess_data);
	while (i < data->num_of_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, routine,
				&data->philo[i]))
			return (1);
		i++;
	}
	pthread_mutex_unlock(&data->acess_data);
	return (0);
}

int	clean_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
		{
			return (1);
		}
		i++;
	}
	return (0);
}
