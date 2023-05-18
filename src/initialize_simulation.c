/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:20:30 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/18 04:24:14 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_data_struct(t_data *data, char **av)
{
	memset(data, 0, sizeof(t_data));
	data->nbr_of_philos = ft_atoi_parser(av[1]);
	if (data->nbr_of_philos == (unsigned long)-1)
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

unsigned long	get_time_in_ms(struct timeval start)
{
	struct timeval stop;
	gettimeofday(&stop, NULL);
	return (((stop.tv_sec - start.tv_sec) * 1000) + ((stop.tv_usec - start.tv_usec) / 1000));
}

// static int	book_places_around_table_for_dinner(t_philo **head, int nbr_philos)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < nbr_philos)
// 		if (insert_back(head, create_and_init_philo(i+1)) == -1)
// 			return (-1);
// 	return (0);
// }

int	init_simulation(t_data *data, char **av)
{
	int	err;

	err = 0;
	err = init_data_struct(data, av);
	if (err == -1)
		return (-1);
	// err = book_places_around_table_for_dinner(&data->philos, data->nbr_of_philos);
	// if (err == -1)
	// 	return (-1);
	return (0);
}

int	init_philo_data(t_philo *philo, t_data *data, int i)
{
	philo->data = data;
	philo->philo_id = i + 1;
	philo->dead_or_alive = 1;
	philo->left_fork = i + 1;
	return (0);
}

int inline	left(int i, int n)
{
	return (i % n);
}

int	right(int i, int n)
{
	return ((i - 1 + n) % n);
}
