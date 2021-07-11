#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define ERROR_MALLOC "ERROR: Unable to allocate memory!\n"
# define ERROR_ARGUMENTS "ERROR: Invalid input!\n"
# define ERROR_SEM "ERROR: Couldn't create semophores!\n"

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>

struct						s_philosophers;

typedef unsigned long		t_time;

typedef struct s_philo
{
	pid_t					pid;
	int						id;
	t_time					last_meal;
	int						feed_one;
	struct s_philosophers	*all;
}	t_philo;

typedef struct s_philosophers
{
	int						nb;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	t_time					start_time;
	int						feed_all;

	t_philo					*ph;
	sem_t					*forks;
	sem_t					*print;
	sem_t					*lock;
	sem_t					*death;
	sem_t					*count_feed;
	pthread_t				pthread;
}	t_philosophers;

void	check_and_init(char **argv, t_philosophers *data, int argc);
void	*life_and_death(t_philosophers *data);

t_time	get_time(void);
t_time	get_current_time(t_time start_time);
void	mod_usleep(int milliseconds, int start_time);

int		error(char *str);
int		ft_atoi(char *str);

#endif