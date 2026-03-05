#include "philo.h"

int main (int ac, char **av)
{
    t_data *data;
    
    if(ac != 5 && ac != 6)
        return printf("Your program(s) must take the following arguments: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"), 0;
    if(input_check(ac, av))
        return printf("Arguments should be positive integers\n"), 1;
    data = (t_data*)malloc(sizeof(t_data));
    if(!data)
        return 1;
    if(prep_data(data, av) || prep_philo(data))
        return free_all(data), printf("Allocation failed\n"), 1;
    if(prep_thread(data))
        return free_all(data), printf("pthread_create() is failed\n"), 1;
    are_you_alive(data);
    if(clean_thread(data))
        return free_all(data), printf("pthread_join() is failed\n"), 1;
    free_all(data);
    return 0;
}