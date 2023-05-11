/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:58:13 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/11 01:27:57 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	insert_back(t_philo **head, t_philo *new_node)
{
	if (!new_node)
		return (-1);
	if (!(*head))
		*head = new_node;
	else
	{
		if (!(*head)->next)
		{	
			(*head)->prev = new_node;
			(*head)->next = new_node;
			new_node->prev = (*head);
		}
		else
		{	
			(*head)->prev->next = new_node;
			new_node->prev = (*head)->prev;
			(*head)->prev = new_node;
		}
		new_node->next = (*head);
	}
	return (0);
}
