#include "philosophers.h"

static void	print_msg(char *str, t_philo *philo)
{
	sem_wait(philo->all->print);
	printf("%lu %d %s\n",
		get_current_time(philo->all->start_time), philo->id + 1, str);
	if (*str == 'd')
		return ;
	sem_post(philo->all->print);
}

static void	*life(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		sem_wait(philo->all->forks);
		print_msg("took a fork", philo);
		sem_wait(philo->all->forks);
		print_msg("took a fork", philo);
		philo->last_meal = get_time();
		print_msg("is a eating", philo);
		if (philo->all->feed_all > 0 && philo->feed_one != philo->all->feed_all)
		{
			philo->feed_one++;
			sem_post(philo->all->count_feed);
		}
		mod_usleep(philo->all->time_to_eat, philo->all->start_time);
		sem_post(philo->all->forks);
		sem_post(philo->all->forks);
		print_msg("is a sleeping", philo);
		mod_usleep(philo->all->time_to_sleep, philo->all->start_time);
		print_msg("is a thinking", philo);
	}
	return (NULL);
}

int	check_death(t_philo *philo)
{
	t_time	time;

	sem_wait(philo->all->lock);
	time = get_time();
	if (time > philo->last_meal + philo->all->time_to_die)
	{
		print_msg("died", philo);
		sem_post(philo->all->death);
		exit (0);
	}
	sem_post(philo->all->lock);
	return (1);
}

void	*life_and_death(t_philosophers *data)
{
	int			i;

	i = 0;
	while (i < data->nb)
	{
		data->ph[i].pid = fork();
		if (data->ph[i].pid == 0)
		{
			data->ph[i].id = i;
			pthread_create(&data->pthread, NULL, (void *)&life, &data->ph[i]);
			pthread_detach(data->pthread);
			while (1)
				check_death(&data->ph[i]);
		}
		else
			i++;
		usleep(100);
	}
	sem_wait(data->death);
	return (0);
}
