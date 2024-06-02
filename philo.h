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
	int		*tab;
	bool	status;
	int		n_philo;
	float	t_die;
	float	t_eat;
	float	t_sleep;
	float	nt_eat;
	size_t	n_meal;
	unsigned long long	gtime;
	unsigned long long	gc_time;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t meal_mutex;
	pthread_mutex_t	sleep_mutex;
	pthread_mutex_t time_mutex;
}			t_inf;

typedef struct s_philo
{
	int 			id;
	unsigned long long	le_time;
	unsigned long long	s_time;
	t_inf			*info;
	pthread_t		thread;
	pthread_t		monitor_thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_philo	*prev;
	struct s_philo	*next;
}	t_philo;


void    initialize_input(char **argv, int argc, t_inf *info);
void    print_status(char *message, t_philo *philo);
void	creat_threads(t_philo **head);
void	*philosofers_routine(void *philos);
void    monitor_routine(t_philo *philo);
unsigned long long  get_time(void);
// void	my_sleep(unsigned int time);
void	my_sleep(t_philo *philo , unsigned int time);
void	printf_element(t_philo *philo);
void	assign_philos(t_philo **head, t_inf *inf);

#endif