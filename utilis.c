/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:54:01 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/06/02 21:23:42 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long  get_time(void)
{
	struct timeval      time;
	unsigned long long  time_s;
	unsigned long long  time_us;

	gettimeofday(&time, NULL);
	time_s = time.tv_sec * 1000;
	time_us = time.tv_usec / 1000.0;
	return (time_s + time_us);
}

void    print_status(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->info->status_mutex);
	if (philo->info->status)
		printf("%llu %d %s\n", get_time() - philo->info->gtime, philo->id, message);
	pthread_mutex_unlock(&philo->info->status_mutex);
}

void my_sleep(t_philo *philo , unsigned int time)
{
	philo->s_time = get_time();
	while (1)
	{
		if (get_time() - philo->s_time >= time)
			break ;
		usleep(50);
	}
}

void    monitor_routine(t_philo *philo)
{

	while (1)
	{
		if (check_time(philo) || check_meal(philo))
			break ;
		pthread_mutex_lock(&philo->info->meal_mutex);
		if (philo->info->tab[philo->id - 1] == philo->info->nt_eat)
		{
			philo->info->n_meal++;
			philo->info->tab[philo->id - 1] = 0;
		}
		pthread_mutex_unlock(&philo->info->meal_mutex);
		philo = philo->next;
	}
}
