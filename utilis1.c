/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:27:54 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/06/07 17:48:06 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memory;
	size_t	check_over;

	check_over = count * size;
	if (count != 0 && size != (check_over / count))
		return (NULL);
	memory = malloc(count * size);
	if (!memory)
		return (NULL);
	memset(memory, 0, count * size);
	return (memory);
}

// void	free_pilosofers(t_philo **head)
// {
// 	int		i;
// 	int		size;
// 	t_philo	*ptr;

// 	i = 0;
// 	size = (*head)->info->n_philo;
// 	while (i < size)
// 	{
// 		ptr = (*head)->next;
// 		free((*head)->right_fork);
// 		free(*head);
// 		*head = ptr;
// 		i++;
// 	}
// 	*head = NULL;
// }

void	ft_error(void)
{
	printf("Use valid format \"number_of_philosophers "
		"time_to_die time_to_eat "
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\" "
		"with positive number.\n");
}
