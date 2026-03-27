/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshirais <dshirais@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:25:02 by dshirais          #+#    #+#             */
/*   Updated: 2026/03/26 16:10:49 by dshirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_philo;

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	pthread_mutex_t	*fork;
	pthread_mutex_t	acess_data;
	int				death;
	struct s_philo	*philo;
	long long		start_time;
	int				total_eat;
	int				*finish_eat;
}					t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	time_manage;
	long long		last_meal;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*access_data;
	int				*death;
	int				*total_eat;
	int				num_of_philo;
	int				*finish_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	int				meal_count;
	long long		start_time;
}					t_philo;

int					input_check(int ac, char **av);
long long			ft_atoll(const char *nptr);
void				free_all(t_data *data);
void				mutex_destroy_data(t_data *data);

int					prep_data(t_data *data, char **av);
int					prep_philo(t_data *data);
void				mutex_init_data(t_data *data);
void				how_many_times(t_data *data, char **av);
void				philo_init(t_data *data, int i);

int					prep_thread(t_data *data);
int					clean_thread(t_data *data);

void				*routine(void *arg);
int					eating(t_philo *philo);
int					sleeping(t_philo *philo);
int					death_check(t_philo *philo, char flag);

void				are_you_alive(t_data *data);
long long			current_time_is(void);

void				reaper_mutex_lock(t_data *data, t_philo *philo);
void				reaper_mutex_unlock(t_data *data, t_philo *philo);
int					reaper_eat_check(t_data *data);
int					reaper_death_check(t_data *data);
void				reaper_kill_program(t_data *data, int i);

void				solo_philo(t_philo *philo);
void				three_philo(t_philo *philo);
void				even_philo(t_philo *philo);
void				odd_philo(t_philo *philo);

void				print_manager(t_philo *philo, char flag);
void				print_taken_fork(t_philo *philo, long long timestamp);
void				print_is_eating(t_philo *philo);
void				print_is_sleeping(t_philo *philo, long long timestamp);
void				print_is_thinking(t_philo *philo, long long timestamp);
void				print_died(t_philo *philo, long long timestamp);

int					are_you_full(t_data *data, int i);
void				mutex_destroy_philo(t_data *data);
pthread_mutex_t		*fork_first(t_philo *philo);
pthread_mutex_t		*fork_second(t_philo *philo);
int					meal_count_check(t_philo *philo);

int smart_sleep(t_philo *philo, long long start_time, char flag);

#endif