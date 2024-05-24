/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:54:01 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/24 17:43:21 by hel-bouk         ###   ########.fr       */
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
    if (philo->info->status)
        printf("%ld %d %s\n", (size_t)(real_time - philo->info->gtime), philo->id, message);
}

void    *monitor_routine(void *philos)
{
    t_philo *philo;

    philo = (t_philo *)philos;
    while (1)
    {
        pthread_mutex_lock(&philo->info->status_mutex);
        if (get_time() - philo->le_time > philo->info->t_die && philo->le_time != 0)
        {
            print_status("died", get_time(), philo);
            philo->info->status = false;
            pthread_mutex_unlock(&philo->info->status_mutex);
            break ;
        }
        pthread_mutex_unlock(&philo->info->status_mutex);
        usleep(1000);
    }
    return (NULL);
}
