/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:27:31 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/22 10:10:07 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosofers_routine(void *philos)
{
    t_philo *philo;
    philo = (t_philo *)philos;

    while (1)
    {
        printf("Philosopher %d is thinking.\n", philo->id);
        printf("right fork : %p\n", philo->right_fork);
        printf("left fork : %p\n", philo->left_fork);
        printf("----------------------------\n");

        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(philo->left_fork);
            pthread_mutex_lock(philo->right_fork);
        }
        else
        {
            pthread_mutex_lock(philo->right_fork);
            pthread_mutex_lock(philo->left_fork);
        }
        printf("Philosopher %d is eating.\n", philo->id);
        usleep(philo->info.t_eat * 1000);

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        printf("Philosopher %d is sleeping.\n", philo->id);
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