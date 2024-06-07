/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:51:08 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/06/07 17:53:27 by hel-bouk         ###   ########.fr       */
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
	if (str[i] != '\0' || result == 0)
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

t_philo	*creat_struct(t_inf *inf)
{
	int	i;
	t_philo *philo;

	i = 0;
	philo = ft_calloc(sizeof(t_philo), inf->n_philo);
	if (!philo)
		return (NULL);
	while (i < (inf)->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].info = inf;
		philo[i].le_time = get_time();
		philo[i].right_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].right_fork, NULL);
		i++;
	}
	return (philo);
}

void	assign_philos(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo[0].info->n_philo  - 1)
	{
		philo[i].left_fork = philo[i + 1].right_fork;
		i++;
	}
	philo[i].left_fork = philo[0].right_fork;
}

void	creat_threads(t_philo *philos)
{
	int		i;

	i = 0;
	philos[0].info->gtime = get_time();
	while (i < philos[0].info->n_philo)
	{
		pthread_create(&(philos[i].thread), NULL, philosofers_routine, philos);
		i++;
	}
	monitor_routine(philos);
	i = 0;
	while (i < philos[0].info->n_philo)
	{
		pthread_join(philos[i].thread, NULL);
		pthread_mutex_destroy(philos[i].right_fork);
		i++;
	}
}
