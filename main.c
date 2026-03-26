/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:23:21 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/26 16:15:39 by dshirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
		return (printf("Arguments should be 4 or 5\n"), 0);
	if (input_check(ac, av))
		return (printf("Arguments should be between 1 and INT_MAX\n"), 1);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (prep_data(data, av) || prep_philo(data))
		return (free_all(data), printf("Allocation failed\n"), 1);
	if (prep_thread(data))
		return (free_all(data), printf("pthread_create() is failed\n"), 1);
	are_you_alive(data);
	if (clean_thread(data))
		return (free_all(data), printf("pthread_join() is failed\n"), 1);
	free_all(data);
	return (0);
}
