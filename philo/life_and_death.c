#include "philosophers.h"

static void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->print);
	printf("%lu %d took a fork\n",
		get_current_time(philo->start_time), philo->id + 1);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(philo->print);
	printf("%lu %d took a fork\n",
		get_current_time(philo->start_time), philo->id + 1);
	printf("%lu %d is eating\n",
		get_current_time(philo->start_time), philo->id + 1);
	if (philo->feed_one >= 0)
		philo->feed_one++;
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->mutex_time);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->mutex_time);
	mod_usleep(philo->time_to_eat, philo->start_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
}

static void	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%lu %d is sleeping\n",
		get_current_time(philo->start_time), philo->id + 1);
	pthread_mutex_unlock(philo->print);
	mod_usleep(philo->time_to_sleep, philo->start_time);
}

static void	is_thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%lu %d is thinking\n",
		get_current_time(philo->start_time), philo->id + 1);
	pthread_mutex_unlock(philo->print);
}

void	*life_and_death(t_philo *philo)
{
	while (1)
	{
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}
