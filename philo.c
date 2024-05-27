/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:27:31 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/27 21:33:43 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosofers_routine(void *philos)
{
    t_philo *philo;

    philo = (t_philo *)philos;
    while (1)
    {
        pthread_mutex_lock(&philo->info->status_mutex);
        if (!philo->info->status)
        {
            pthread_mutex_unlock(&philo->info->status_mutex);
            break ;
        }
        pthread_mutex_unlock(&philo->info->status_mutex);
        
        print_status("is thinking", philo);
        if (philo->id % 2 == 0)
        {
            print_status("has taken a fork", philo);
            pthread_mutex_lock(philo->left_fork);
            pthread_mutex_lock(philo->right_fork);
        }
        else
        {
            print_status("has taken a fork", philo);
            pthread_mutex_lock(philo->right_fork);
            pthread_mutex_lock(philo->left_fork);
        }
        
        pthread_mutex_lock(&philo->info->time_mutex);
        philo->le_time = get_time();
        pthread_mutex_unlock(&philo->info->time_mutex);
        
        print_status("is eating", philo);
        my_sleep(philo->info->t_eat);

        pthread_mutex_lock(&philo->info->meal_mutex);
        philo->info->tab[philo->id]++;
        pthread_mutex_unlock(&philo->info->meal_mutex);

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        print_status("is sleeping", philo);
        my_sleep(philo->info->t_sleep);
        
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
 
    // for (int i =0; i <= 100; i++)
    // {
    //     printf("-----------------------\n");
    //     double old_time = get_time();
    //     printf("old_time %f\n", old_time);
    //     my_sleep(200);
    //     double new_time = get_time();
    //     printf("new_time %f\n", new_time);
    //     printf("time increment %f\n", new_time - old_time);
    //     printf("-----------------------\n");
    // }
        
	}
    
	return (0);
}