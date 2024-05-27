/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:54:01 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/05/27 21:42:16 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long  get_time(void)
{
    struct timeval      time;
    unsigned long long  time_s;
    unsigned long long  time_us;

    gettimeofday(&time, NULL);
    time_s = time.tv_sec * 1000;
    time_us = time.tv_usec / 1000.0;
    return (time_s + time_us);
}

void    print_status(char *message, t_philo *philo)
{
    pthread_mutex_lock(&philo->info->status_mutex);
    if (philo->info->status)
        printf("%llu %d %s\n", get_time() - philo->info->gtime, philo->id, message);
    pthread_mutex_unlock(&philo->info->status_mutex);
}

void my_sleep(unsigned int milliseconds)
{
    struct timeval current_time;
    struct timeval end_time;
    // unsigned int microseconds_to_sleep;

    gettimeofday(&current_time, NULL);

    // Calculate the end time
    end_time.tv_sec = current_time.tv_sec + milliseconds / 1000;
    end_time.tv_usec = current_time.tv_usec + (milliseconds % 1000) * 1000;

    // Adjust end time if microseconds overflow
    if (end_time.tv_usec >= 1000000) {
        end_time.tv_sec++;
        end_time.tv_usec -= 1000000;
    }

    // Sleep until the desired time
    while ((current_time.tv_sec < end_time.tv_sec) ||
           (current_time.tv_sec == end_time.tv_sec && current_time.tv_usec < end_time.tv_usec)) {
        gettimeofday(&current_time, NULL);
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
        if (get_time() - philo->le_time >= philo->info->t_die || n_meal == philo->info->n_philo)
        {
            pthread_mutex_unlock(&philo->info->time_mutex);
            if (n_meal != philo->info->n_philo)
                print_status("died",philo);
            pthread_mutex_lock(&philo->info->status_mutex);
            philo->info->status = false;
            pthread_mutex_unlock(&philo->info->status_mutex);
            break ;
        }
        pthread_mutex_unlock(&philo->info->time_mutex);
        pthread_mutex_lock(&philo->info->meal_mutex);
        if (philo->info->tab[philo->id] == philo->info->nt_eat)
        {
            philo->info->tab[philo->id] = 0;
            n_meal++;
        }
        pthread_mutex_unlock(&philo->info->meal_mutex);
    }
    return (NULL);
}
