/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:27:31 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/26 16:51:47 by hel-bouk         ###   ########.fr       */
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
        
        pthread_mutex_lock(&philo->info->time_mutex);
        philo->le_time = get_time();
        philo->current_time = philo->le_time;
        pthread_mutex_unlock(&philo->info->time_mutex);
        
        print_status("is eating", get_time(), philo);
        // pthread_mutex_lock(&philo->info->sleep_mutex);
        my_sleep(philo->info->t_eat, philo);
        // usleep(philo->info->t_eat * 1000);
        // pthread_mutex_unlock(&philo->info->sleep_mutex);

        // pthread_mutex_lock(&philo->info->meal_mutex);
        // philo->info->tab[philo->id]++;
        // pthread_mutex_unlock(&philo->info->meal_mutex);

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        pthread_mutex_lock(&philo->info->time_mutex);
        philo->current_time = get_time();
        pthread_mutex_unlock(&philo->info->time_mutex);
        
        print_status("is sleeping", get_time(), philo);
        // pthread_mutex_lock(&philo->info->sleep_mutex);
        my_sleep(philo->info->t_sleep,  philo);
        // usleep(philo->info->t_sleep * 1000);
        // pthread_mutex_unlock(&philo->info->sleep_mutex);
        
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
        // philos->le_time = get_time();
        // printf("le_time == %f\n", philos->le_time);
        // for (int i =0; i <= 10; i++)
        // {
        //     printf("-----------------------\n");
        //     printf("old_time %ld\n", (size_t)get_time());
        //     my_sleep(200, philos);
        //     printf("new_time %ld\n", (size_t)get_time());
        //     printf("-----------------------\n");
            
        // }
        
	}
    
	return (0);
}