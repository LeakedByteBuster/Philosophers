/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:53:13 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/15 05:47:52 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

t_philo	*create_and_init_philo(int content)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo));
	philo->philo_id = content;
	// philo->my_fork = 1;
	philo->dead_or_alive = 1;
	// philo->curr_state = THINKING;
	return (philo);
}
