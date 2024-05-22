/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:27:31 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/22 15:48:04 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosofers_routine(void *philos)
{
    t_philo *philo;

    philo = (t_philo *)philos;
    while (1)
    {
        printf("%ld %d  is thinking\n", (unsigned long)(get_time() - philo->info.gtime),  philo->id);
        if (philo->id % 2 == 0)
        {
            printf("%ld %d has taken a fork\n", (unsigned long)(get_time() - philo->info.gtime), philo->id);
            pthread_mutex_lock(philo->left_fork);
            pthread_mutex_lock(philo->right_fork);
        }
        else
        {
            printf("%ld %d has taken a fork\n", (unsigned long)(get_time() - philo->info.gtime), philo->id);
            pthread_mutex_lock(philo->right_fork);
            pthread_mutex_lock(philo->left_fork);
        }
        philo->le_time = get_time();
        printf("%ld %d is eating\n", (unsigned long)(get_time() - philo->info.gtime), philo->id);
        usleep(philo->info.t_eat * 1000);

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        printf("%ld %d  is sleeping\n", (unsigned long)(get_time() - philo->info.gtime), philo->id);
        usleep(philo->info.t_sleep * 1000);
    }
    return (NULL);
}


int main(int argc, char **argv)
{
	int			i;
	t_main      main;

	i = 0;
	main.philo = NULL;
	if (argc == 5 || argc == 6)
	{
		initialize_input(argv, argc, &(main.info));
		assign_philos(&(main.philo), &main);
        creat_threads(&(main.philo));
	}
	return (0);
}