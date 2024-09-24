#include "../philo.h"
#include <pthread.h>

void	what_first_time(t_args *args)
{
    struct timeval	tv;

	gettimeofday(&tv, NULL);
    args->first_time = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

unsigned long	what_time(t_args *args)
{
    struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - args->first_time);
}

void	my_usleep(unsigned long my_time, t_args *args)
{
	unsigned long	time_to_wait;
	unsigned long	first_time;
	unsigned long what_is_time;

	first_time = what_time(args);
	time_to_wait = first_time + my_time;;
	what_is_time = what_time(args);
	while (what_is_time < time_to_wait)
	{
		pthread_mutex_lock(&args->mutex);
		if (args->die == 1)
		{
			pthread_mutex_unlock(&args->mutex);
			return ;
		}
		pthread_mutex_unlock(&args->mutex);
		usleep (20);
		what_is_time = what_time(args);

	}
}
