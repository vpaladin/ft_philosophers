#include "philosophers.h"

static void	init_philo(t_philosophers *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->nb)
	{
		data->ph[i].id = i;
		data->ph[i].last_meal = data->start_time;
		data->ph[i].print = &data->print;
		data->ph[i].start_time = data->start_time;
		data->ph[i].mutex_time = &data->mutex_time;
		data->ph[i].time_to_eat = data->time_to_eat;
		data->ph[i].time_to_sleep = data->time_to_sleep;
		pthread_mutex_init(&data->ph[i].right_fork, NULL);
		if (data->feed_all > 0)
			data->ph[i].feed_one = 0;
		i++;
	}
}

static void	init_left_fork(t_philosophers *data)
{
	int	i;

	i = -1;
	while (++i < data->nb)
	{
		if (i == 0)
			data->ph[i].left_fork = &data->ph[data->nb - 1].right_fork;
		else
			data->ph[i].left_fork = &data->ph[i - 1].right_fork;
	}
}

static int	init_time_and_eat(char **argv, t_philosophers *data, int argc)
{
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nb = ft_atoi(argv[1]);
	if (argc == 6)
	{
		data->feed_all = ft_atoi(argv[5]);
		if (data->feed_all < 0)
			return (error(ERROR_ARGUMENTS));
		else if (data->feed_all == 0)
			return (0);
	}
	else
		data->feed_all = -100;
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60 || data->nb <= 0)
		return (error(ERROR_ARGUMENTS));
	return (1);
}

int	check_and_init(char **argv, t_philosophers *data, int argc)
{
	if (init_time_and_eat(argv, data, argc) == 0)
		return (0);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->mutex_time, NULL);
	data->ph = malloc(sizeof(t_philo) * data->nb);
	if (data->ph == NULL)
		return (error(ERROR_MALLOC));
	init_philo(data);
	init_left_fork(data);
	return (1);
}
