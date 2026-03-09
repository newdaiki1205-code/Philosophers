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


long long current_time_is()
{
	struct timeval current_time;
	long long re;

	gettimeofday(&current_time, NULL);
    re = (long long)current_time.tv_sec * 1000 + (current_time.tv_usec / 1000);
	return re;
}