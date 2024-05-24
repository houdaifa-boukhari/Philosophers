/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:27:31 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/24 17:22:02 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosofers_routine(void *philos)
{
    t_philo *philo;

    philo = (t_philo *)philos;
    while (philo->info->status)
    {
        print_status("is thinking", get_time(), philo);
        if (philo->id % 2 == 0)
        {
            print_status("has taken a fork", get_time(), philo);
            pthread_mutex_lock(philo->left_fork);
            pthread_mutex_lock(philo->right_fork);
        }
        else
        {
            print_status("has taken a fork", get_time(), philo);
            pthread_mutex_lock(philo->right_fork);
            pthread_mutex_lock(philo->left_fork);
        }
        pthread_mutex_lock(&philo->info->status_mutex);
        philo->le_time = get_time();
        pthread_mutex_unlock(&philo->info->status_mutex);
        
        print_status("is eating", get_time(), philo);
        usleep(philo->info->t_eat * 1000);

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        print_status("is sleeping", get_time(), philo);
        usleep(philo->info->t_sleep * 1000);
        
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
	}
    
	return (0);
}