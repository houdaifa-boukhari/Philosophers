#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_inf
{
	int		n_philo;
	float	t_die;
	float	t_eat;
	float	t_sleep;
	float	nt_eat;
}			t_inf;

typedef struct s_philo
{
	int 			id;
	double				time;
	t_inf			info;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_philo	*prev;
	struct s_philo	*next;
}	t_philo;

typedef struct s_main
{
	t_inf	info;
	t_philo	*philo;
}			t_main;

void    initialize_input(char **argv, int argc, t_inf *info);
void	assign_philos(t_philo **head, t_main *main);
void	creat_threads(t_philo **head);
void	*philosofers_routine(void *philos);
double   get_time(void);

#endif