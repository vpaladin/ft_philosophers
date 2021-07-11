#include "philosophers.h"

void	mod_usleep(int milliseconds, int start_time)
{
	time_t	stop;
	time_t	start;

	stop = ((time_t)get_current_time(start_time)) + milliseconds;
	start = (time_t)get_current_time(start_time);
	while (start < stop)
	{
		usleep(50);
		start = (time_t)get_current_time(start_time);
	}
}

t_time	get_time(void)
{
	struct timeval		time;
	t_time				ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

t_time	get_current_time(t_time start_time)
{
	struct timeval	tp_start;
	long			current_time;

	gettimeofday(&tp_start, NULL);
	current_time = tp_start.tv_sec * 1000 + tp_start.tv_usec / 1000;
	return (current_time - start_time);
}
