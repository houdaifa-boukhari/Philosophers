/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:54:01 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/22 15:51:36 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

double   get_time(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000.0 + time.tv_usec / 1000.0);
}

void    *monitor_routine(void *philos)
{
    t_philo *philo;

    philo = (t_philo *)philos;
    while (1)
    {
         if (get_time() - philo->le_time > philo->info.t_die) {
            printf("%ld %d died\n", (unsigned long)(get_time() - philo->info.gtime), philo->id);
            exit(1);
        }
        usleep(1000);
    }
}