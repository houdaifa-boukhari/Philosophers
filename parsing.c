/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:51:08 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/06/03 12:10:59 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str, int *flag)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (str[i] == '+')
		i++;
	if (!str || !(str[i] >= '0' && str[i] <= '9'))
		*flag = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if ((result > INT_MAX))
		{
			*flag = 1;
			break ;
		}
		i++;
	}
	if (str[i] != '\0')
		*flag = 1;
	return (result);
}

bool	initialize_input(char **argv, int argc, t_inf *info)
{
	int	flag;

	flag = 0;
	info->n_philo = ft_atoi(argv[1], &flag);
	info->t_die = ft_atoi(argv[2], &flag);
	info->t_eat = ft_atoi(argv[3], &flag);
	info->t_sleep = ft_atoi(argv[4], &flag);
	info->status = true;
	info->n_meal = 0;
	if (argc == 6)
		info->nt_eat = ft_atoi(argv[5], &flag);
	else
		info->nt_eat = -1;
	if (flag == 1)
	{
		ft_error();
		return (false);
	}
	info->tab = ft_calloc(sizeof(int), info->n_philo);
	if (!info->tab)
		return (false);
	pthread_mutex_init(&info->meal_mutex, NULL);
	pthread_mutex_init(&info->status_mutex, NULL);
	pthread_mutex_init(&info->time_mutex, NULL);
	return (true);
}

void	creat_list(int id, t_inf **info, t_philo **head)
{
	t_philo	*philos;
	t_philo	*ptr;

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

void	assign_philos(t_philo **head, t_inf *inf)
{
	int		i;
	t_philo	*philos;

	i = 1;
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

void	creat_threads(t_philo **head)
{
	int		i;
	t_philo	*philos;

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
	i = 0;
	while (i < philos->info->n_philo)
	{
		pthread_join(philos->thread, NULL);
		philos = philos->next;
		i++;
	}
}
