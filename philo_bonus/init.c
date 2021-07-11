#include "philosophers.h"

static void	init_philo(t_philosophers *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->nb)
	{
		data->ph[i].last_meal = data->start_time;
		if (data->feed_all > 0)
			data->ph[i].feed_one = 0;
		data->ph[i].all = data;
		i++;
	}
}

static void	init_semaphores(t_philosophers *data)
{
	sem_unlink("forks");
	data->forks = sem_open("forks", O_CREAT, S_IRWXU, data->nb);
	sem_unlink("print");
	data->print = sem_open("print", O_CREAT, S_IRWXU, 1);
	sem_unlink("lock");
	data->lock = sem_open("lock", O_CREAT, S_IRWXU, 1);
	if (data->feed_all > 0)
	{
		sem_unlink("count_feed");
		data->count_feed = sem_open("count_feed", O_CREAT, S_IRWXU, 0);
		if (data->count_feed == SEM_FAILED)
			error(ERROR_SEM);
	}
	sem_unlink("death");
	data->death = sem_open("death", O_CREAT, S_IRWXU, 0);
	if (data->forks == SEM_FAILED || data->print == SEM_FAILED
		||data->death == SEM_FAILED || data->lock == SEM_FAILED)
		error(ERROR_SEM);
}

static void	init_time_and_eat(char **argv, t_philosophers *data, int argc)
{
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nb = ft_atoi(argv[1]);
	if (argc == 6)
	{
		data->feed_all = ft_atoi(argv[5]);
		if (data->feed_all < 0)
			error(ERROR_ARGUMENTS);
		else if (data->feed_all == 0)
			exit (0);
	}
	else
		data->feed_all = -100;
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60 || data->nb <= 0)
		error(ERROR_ARGUMENTS);
}

void	check_and_init(char **argv, t_philosophers *data, int argc)
{
	init_time_and_eat(argv, data, argc);
	init_semaphores(data);
	data->ph = malloc(sizeof(t_philo) * data->nb);
	if (data->ph == NULL)
		error(ERROR_MALLOC);
	init_philo(data);
}
