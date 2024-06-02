/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:51:08 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/06/02 19:47:18 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void    initialize_input(char **argv, int argc, t_inf *info)
{
	info->n_philo = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	info->status = true;
	info->n_meal = 0;
	info->tab = calloc(sizeof(int), info->n_philo);
	if (!info->tab)
		return ;
	pthread_mutex_init(&info->meal_mutex, NULL);
	pthread_mutex_init(&info->status_mutex, NULL);
	pthread_mutex_init(&info->sleep_mutex, NULL);
	pthread_mutex_init(&info->time_mutex, NULL);
	if (argc == 6)
	    info->nt_eat = ft_atoi(argv[5]);
    else
        info->nt_eat = -1;
}

void	creat_list(int id, t_inf **info, t_philo **head)
{
	t_philo	*philos;
	t_philo	*ptr;

	if (!head)
		return ;
	philos = malloc(sizeof(t_philo));
	if (!philos)
		return ;
	philos->id = id;
	philos->info = *info;
	philos->le_time = get_time();
	philos->right_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philos->right_fork, NULL);
	philos->next = NULL;
	if (!*head)
	{
		philos->prev = NULL;
		*head = philos;
		return ;
	}
	ptr = *head;
	while (ptr->next)
		ptr = ptr->next;
	philos->prev = ptr;
	ptr->next = philos;
	return ;
}

void printf_element(t_philo *philo)
{
	while (philo)
	{
		printf("philosfers id : %d\n", philo->id);
		printf("status : %d\n", philo->info->status);
		printf("----------------------------\n");
		philo = philo->next;
	}
}

void	assign_philos(t_philo **head, t_inf *inf)
{
	int			i;
	t_philo		*philos;

	i  = 1;
	while (i <= inf->n_philo)
		creat_list(i++, &inf, head);
	philos = (*head);
	while (philos->next)
	{
		philos->left_fork = philos->next->right_fork;
		philos = philos->next;
	}
	philos->left_fork = (*head)->right_fork;
}

void	cercle_linked(t_philo **head)
{
	t_philo		*philos;
	t_philo		*ptr;

	philos = *head;
	ptr = philos;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = philos;
	philos->prev = ptr;
		
}

void	creat_threads(t_philo **head)
{
	int			i;
	t_philo		*philos;

	i = 0;
	philos = *head;
	cercle_linked(head);
	philos->info->gtime = get_time();
	while (i < philos->info->n_philo)
	{
		pthread_create(&(philos->thread), NULL, philosofers_routine, philos);
		philos = philos->next;
		i++;
	}
	philos = *head;
	monitor_routine(philos);
	printf("hello\n");
	i = 0;
	while (i < philos->info->n_philo)
	{
		pthread_join(philos->thread, NULL);
		philos = philos->next;
		i++;
	}
}
