/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:20:30 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/20 05:36:18 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//	parse and store given arguments in data struct
int	init_data_struct(t_data *data, char **av)
{
	memset(data, 0, sizeof(t_data));
	data->nbr_of_philos = ft_atoi_parser(av[1]);
	if (data->nbr_of_philos == (unsigned long)-1 || data->nbr_of_philos == 0
		|| data->nbr_of_philos > 200)
		return (-1);
	data->time_to_die = ft_atoi_parser(av[2]);
	if (data->time_to_die == (unsigned long)-1)
		return (-1);
	data->time_to_eat = ft_atoi_parser(av[3]);
	if (data->time_to_eat == (unsigned long)-1)
		return (-1);
	data->time_to_sleep = ft_atoi_parser(av[4]);
	if (data->time_to_sleep == (unsigned long)-1)
		return (-1);
	if (av[5])
	{	
		data->number_of_meals = ft_atoi_parser(av[5]);
		if (data->number_of_meals == (unsigned long)-1)
			return (-1);
	}
	return (0);
}

//	Initialize variable in data struct
int	init_philo_data(t_philo *philo, t_data *data, int i)
{
	philo->data = data;
	philo->philo_id = i + 1;
	philo->status = ALIVE;
	pthread_mutex_lock(&data->data_mtx);
	if (data->nbr_of_philos < 2)
		philo->fork = 0;
	else
		philo->fork = i + 1;
	pthread_mutex_unlock(&data->data_mtx);
	return (0);
}

//	kills the philo pointed to by "data->philo->head"
void	take_philo_soul(t_data **data)
{
	pthread_mutex_lock(&(*data)->philo_head->death_mtx);
	(*data)->philo_head->status = DEAD;
	pthread_mutex_unlock(&(*data)->philo_head->death_mtx);
	(*data)->philo_head = (*data)->philo_head->next;
}
