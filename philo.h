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
	pthread_mutex_t	status_mutex;
	bool	status;
	int		n_philo;
	float	t_die;
	float	t_eat;
	float	t_sleep;
	float	nt_eat;
	double	gtime;
}			t_inf;

typedef struct s_philo
{
	int 			id;
	t_inf			*info;
	pthread_t		thread;
	pthread_t		monitor_thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	unsigned long	le_time;
	struct s_philo	*prev;
	struct s_philo	*next;
}	t_philo;

typedef struct s_main
{
	t_inf	info;
	t_philo	*philo;
}			t_main;

void    initialize_input(char **argv, int argc, t_inf *info);
void    print_status(char *message, double real_time, t_philo *philo);
void	creat_threads(t_philo **head);
void	*philosofers_routine(void *philos);
void    *monitor_routine(void *pilos);
double   get_time(void);
void printf_element(t_philo *philo);
void	assign_philos(t_philo **head, t_inf *inf);

#endif