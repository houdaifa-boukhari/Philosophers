/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-bouk <hel-bouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:27:54 by hel-bouk          #+#    #+#             */
/*   Updated: 2024/06/03 11:33:45 by hel-bouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (len > 0)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
		len--;
	}
	return (b);
}

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
	ft_memset(memory, 0, count * size);
	return (memory);
}

void	free_pilosofers(t_philo **head)
{
	int		i;
	int		size;
	t_philo	*ptr;

	i = 0;
	size = (*head)->info->n_philo;
	while (i < size)
	{
		ptr = (*head)->next;
		free((*head)->right_fork);
		free(*head);
		*head = ptr;
		i++;
	}
	*head = NULL;
}
