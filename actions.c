/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:10:47 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/06/03 15:06:07 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status("has taken a fork", philo);
	if (philo->right_fork == philo->left_fork)
		return (false);
	pthread_mutex_lock(philo->left_fork);
	print_status("has taken a fork", philo);
	return (true);
}

void	eating(t_philo *philo)
{
	print_status("is eating", philo);
	my_sleep(philo, philo->info->t_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(&philo->info->meal_mutex);
	philo->info->tab[philo->id - 1]++;
	pthread_mutex_unlock(&philo->info->meal_mutex);
}

bool	check_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->time_mutex);
	philo->cle_time = philo->le_time;
	pthread_mutex_unlock(&philo->info->time_mutex);
	if (get_time() - philo->cle_time >= philo->info->t_die)
	{
		pthread_mutex_lock(&philo->info->status_mutex);
		philo->info->status = false;
		pthread_mutex_unlock(&philo->info->status_mutex);
		if (philo->info->n_meal != (size_t)philo->info->n_philo)
			printf("%llu %d %s\n", get_time() - philo->info->gtime, philo->id,
				"died");
		return (true);
	}
	return (false);
}

bool	check_meal(t_philo *philo)
{
	if (philo->info->n_meal >= (size_t)philo->info->n_philo)
	{
		pthread_mutex_lock(&philo->info->status_mutex);
		philo->info->status = false;
		pthread_mutex_unlock(&philo->info->status_mutex);
		return (true);
	}
	return (false);
}
