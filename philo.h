/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:27:07 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/06/03 12:11:21 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_inf
{
	int					*tab;
	bool				status;
	int					n_philo;
	float				t_die;
	float				t_eat;
	float				t_sleep;
	float				nt_eat;
	size_t				n_meal;
	unsigned long long	gtime;
	unsigned long long	gc_time;
	pthread_mutex_t		status_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		time_mutex;
}						t_inf;

typedef struct s_philo
{
	int					id;
	unsigned long long	le_time;
	unsigned long long	s_time;
	t_inf				*info;
	pthread_t			thread;
	pthread_t			monitor_thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_philo		*prev;
	struct s_philo		*next;
}						t_philo;

bool					initialize_input(char **argv, int argc, t_inf *info);
void					print_status(char *message, t_philo *philo);
void					creat_threads(t_philo **head);
void					*philosofers_routine(void *philos);
void					monitor_routine(t_philo *philo);
void					free_pilosofers(t_philo **head);
void					my_sleep(t_philo *philo, unsigned int time);
void					assign_philos(t_philo **head, t_inf *inf);
void					*ft_calloc(size_t count, size_t size);
void					cercle_linked(t_philo **head);
bool					take_fork(t_philo *philos);
void					eating(t_philo *philo);
bool					check_time(t_philo *philo);
bool					check_meal(t_philo *philo);
void					ft_error(void);
unsigned long long		get_time(void);

#endif