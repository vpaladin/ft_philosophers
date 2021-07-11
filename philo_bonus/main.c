#include "philosophers.h"

static void	*check_feed(t_philosophers *data)
{
	int	need_count_eat;

	need_count_eat = 1;
	while (need_count_eat <= data->nb * data->feed_all) // 5 philo need eat 7
	{
		sem_wait(data->count_feed);
		need_count_eat++;
	}
	sem_post(data->death);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philosophers	data;
	int				i;
	pthread_t		need_count_eat;

	if (argc != 5 && argc != 6)
		error(ERROR_ARGUMENTS);
	check_and_init(argv, &data, argc);
	if (data.feed_all > 0)
	{
		pthread_create(&need_count_eat, NULL, (void *)&check_feed, &data);
		pthread_detach(need_count_eat);
	}
	pthread_create(&data.pthread, NULL, (void *)&life_and_death, &data);
	pthread_join(data.pthread, NULL);
	i = 0;
	while (i < data.nb)
	{
		kill(data.ph[i].pid, SIGKILL);
		i++;
	}
	free(data.ph);
	exit(0);
	return (0);
}
