/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 01:51:08 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/11 01:54:01 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clear_list(t_philo *head, int list_size)
{
	t_philo	*tmp;

	if (!head || list_size == 0)
		return ;
	while (list_size)
	{
		tmp = head;
		head = head->next;
		free(tmp);
		list_size--;
	}
	return ;
}
