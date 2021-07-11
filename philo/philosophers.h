#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define ERROR_MALLOC "ERROR: Unable to allocate memory!\n"
# define ERROR_ARGUMENTS "ERROR: Invalid input!\n"
# define ERROR_TREADS "ERROR: Couldn't create thread!\n"

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <time.h>
# include <stdio.h>

typedef unsigned long	t_time;

typedef struct s_philo
{
	int					id;
	t_time				last_meal;
	t_time				start_time;
	int					time_to_eat;
	int					time_to_sleep;
	int					feed_one;

	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*print;
	pthread_mutex_t		*mutex_time;

	pthread_mutex_t		right_fork;
	pthread_t			thread;
}	t_philo;

typedef struct s_philosophers
{
	int					nb;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	t_time				start_time;

	int					feed_all;

	t_philo				*ph;
	pthread_mutex_t		print;
	pthread_mutex_t		mutex_time;
	pthread_t			death_status;
}	t_philosophers;

int		check_and_init(char **argv, t_philosophers *data, int argc);

void	*life_and_death(t_philo *philo);

int		error(char *str);

t_time	get_time(void);
t_time	get_current_time(t_time start_time);
void	mod_usleep(int milliseconds, int start_time);

void	ft_putstr(char *str);
int		ft_atoi(char *str);

#endif