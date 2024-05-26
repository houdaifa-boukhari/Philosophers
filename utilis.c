/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:54:01 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/26 16:49:09 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

double   get_time(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000.0 + time.tv_usec / 1000.0);
}

void    print_status(char *message, double real_time, t_philo *philo)
{
    pthread_mutex_lock(&philo->info->status_mutex);
    if (philo->info->status)
        printf("%ld %d %s\n", (size_t)(real_time - philo->info->gtime), philo->id, message);
    pthread_mutex_unlock(&philo->info->status_mutex);
}

void    my_sleep(float time, t_philo *philo)
{

    while (1)
    {
        // printf("(%f) - (%f)== %f)\n", get_time(), philo->le_time, (get_time() - philo->le_time));
        if ((get_time() - philo->current_time) >= time)
            break ;
    }
}

void    *monitor_routine(void *philos)
{
    t_philo *philo;
    size_t  *time;
    int     n_meal;

    n_meal = 0;
    philo = (t_philo *)philos;
    time = calloc(sizeof(size_t), philo->info->n_philo);
    if (!time)
        return NULL;
    while (1)
    {
        pthread_mutex_lock(&philo->info->time_mutex);
        time[philo->id] = philo->le_time;
        pthread_mutex_unlock(&philo->info->time_mutex);
        if ((size_t)(get_time() - time[philo->id]) > philo->info->t_die && time[philo->id] != 0) // n_meal == philo->info->n_philo
        {
            // if (n_meal != philo->info->n_philo)
            // print_status("died", get_time(), philo);
            pthread_mutex_lock(&philo->info->status_mutex);
            // philo->info->status = false;
            pthread_mutex_unlock(&philo->info->status_mutex);
            break ;
        }
        // else if (time != 0)
        //     printf("last philo : %d eat when %ld\n", philo->id, (size_t)(get_time() - time));
        // pthread_mutex_lock(&philo->info->meal_mutex);
        // if (philo->info->tab[philo->id] == philo->info->nt_eat)
        //         n_meal++;
        // pthread_mutex_unlock(&philo->info->meal_mutex);
        // usleep(1000);
    }
    return (NULL);
}
