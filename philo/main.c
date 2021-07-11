#include "philosophers.h"

static void	freedom_for_all(t_philosophers data)
{
	int	i;

	i = -1;
	while (++i < data.nb)
	{
		pthread_detach(data.ph[i].thread);
	}
	i = -1;
	while (++i < data.nb)
		pthread_mutex_destroy(&data.ph[i].right_fork);
	pthread_mutex_destroy(&data.print);
	pthread_mutex_destroy(&data.mutex_time);
	free(data.ph);
}

static int	feed(t_philosophers *data)
{
	int	i;
	int	full_philosophers;

	i = 0;
	full_philosophers = 0;
	while (i < data->nb)
	{
		if (data->ph[i].feed_one >= data->feed_all)
			full_philosophers++;
		i++;
	}
	if (full_philosophers >= data->nb)
		return (1);
	else
		return (0);
}

static int	check_death(t_philosophers *data, int index)
{
	t_time			time;

	pthread_mutex_lock(&data->mutex_time);
	time = get_time();
	if (time >= data->ph[index].last_meal + data->time_to_die)
	{
		pthread_mutex_lock(&data->print);
		usleep(1000);
		printf("%lu %d died\n",
			get_current_time(data->start_time), data->ph[index].id + 1);
		return (1);
	}
	return (0);
}

static void	*death_status(t_philosophers *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (data->nb > ++i)
		{
			if (check_death(data, i))
				return (NULL);
			pthread_mutex_unlock(&data->mutex_time);
			if (feed(data) == 1 && data->feed_all > 0)
			{
				pthread_mutex_lock(&data->print);
				return (NULL);
			}
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philosophers	data;
	int				i;

	if (argc != 5 && argc != 6)
		return (error(ERROR_ARGUMENTS));
	if (check_and_init(argv, &data, argc) == 0)
		return (0);
	i = 0;
	while (i < data.nb)
	{
		pthread_create(&data.ph[i].thread, NULL,
			(void *)&life_and_death, &data.ph[i]);
		usleep(100);
		i++;
	}
	pthread_create(&data.death_status, NULL, (void *)&death_status, &data);
	pthread_join(data.death_status, NULL);
	freedom_for_all(data);
	return (0);
}
