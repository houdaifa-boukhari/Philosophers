/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:27:31 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/06/02 21:20:27 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void *philosofers_routine(void *philos)
{
	t_philo *philo;

	philo = (t_philo *)philos;
	if (((philo->id) % 2) == 0)
	{
		print_status("is sleeping", philo);
		my_sleep(philo, philo->info->t_sleep);
	}
	while (philo->info->status)
	{
		print_status("is thinking", philo);
		if (!take_fork(philo))
			break ;
		pthread_mutex_lock(&philo->info->time_mutex);
		philo->le_time = get_time();
		pthread_mutex_unlock(&philo->info->time_mutex);
		eating(philo);
		print_status("is sleeping", philo);
		my_sleep(philo, philo->info->t_sleep);
		pthread_mutex_lock(&philo->info->status_mutex);
		pthread_mutex_unlock(&philo->info->status_mutex);
	}
	return (NULL);
}


int main(int argc, char **argv)
{
	int			i;
	t_philo    *philos;
	t_inf     info;

	i = 0;
	philos = NULL;
	if (argc == 5 || argc == 6)
	{
		initialize_input(argv, argc, &info);
		assign_philos(&philos, &info);
		creat_threads(&philos);
		pthread_mutex_destroy(&info.status_mutex);
		pthread_mutex_destroy(&info.meal_mutex);
		pthread_mutex_destroy(philos->right_fork);
		pthread_mutex_destroy(philos->left_fork);
		pthread_mutex_destroy(&info.sleep_mutex);
		pthread_mutex_destroy(&info.time_mutex);
	}
	return (0);
}