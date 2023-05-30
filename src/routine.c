/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 03:36:26 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/30 04:44:53 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	unsigned long	start_time;

	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%lu	%lu is eating\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mtx);
	start_time = get_time_in_ms(philo->start);
	pthread_mutex_lock(&philo->death_mtx);
	while (((get_time_in_ms(philo->start) - start_time)
			< philo->data->time_to_eat) && (philo->status == ALIVE))
	{
		pthread_mutex_unlock(&philo->death_mtx);
		usleep(100);
		pthread_mutex_lock(&philo->death_mtx);
	}
	philo->last_meal = get_time_in_ms(philo->start);
	pthread_mutex_unlock(&philo->death_mtx);
	philo->nbr_of_meals_taken += 1;
	return ;
}

void	ft_sleep(t_philo *philo)
{
	unsigned long	start_time;

	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%lu	%lu is sleeping\n", get_time_in_ms(philo->start),
		philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mtx);
	start_time = get_time_in_ms(philo->start);
	pthread_mutex_lock(&philo->death_mtx);
	while (((get_time_in_ms(philo->start) - start_time)
			< philo->data->time_to_sleep) && (philo->status == ALIVE))
	{
		pthread_mutex_unlock(&philo->death_mtx);
		usleep(100);
		pthread_mutex_lock(&philo->death_mtx);
	}
	pthread_mutex_unlock(&philo->death_mtx);
	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%lu	%lu is thinking\n", get_time_in_ms(philo->start),
		philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mtx);
	return ;
}

int	pick_forks(t_philo *philo)
{
	unsigned long	start_time;

	pthread_mutex_lock(&philo->data->data_mtx);
	if (philo->prev->fork)
	{
		pthread_mutex_lock(&philo->prev->mtx);
		printf("%lu	%lu has taken a fork\n", get_time_in_ms(philo->start),
			philo->philo_id);
	}
	else
	{
		start_time = get_time_in_ms(philo->start);
		while (((get_time_in_ms(philo->start) - start_time)
				< philo->data->time_to_die +1))
			usleep(100);
		pthread_mutex_unlock(&philo->data->data_mtx);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->data_mtx);
	pthread_mutex_lock(&philo->mtx);
	printf("%lu	%lu has taken a fork\n", get_time_in_ms(philo->start),
		philo->philo_id);
	return (0);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->mtx);
	pthread_mutex_unlock(&philo->prev->mtx);
	return ;
}

void	grim_reaper(t_data *data)
{
	while (1 && data->simulation)
	{
		pthread_mutex_lock(&data->philo_head->death_mtx);
		if ((get_time_in_ms(data->start) - data->philo_head->last_meal)
			> data->time_to_die)
		{
			pthread_mutex_unlock(&data->philo_head->death_mtx);
			data->death_id = data->philo_head->philo_id;
			take_philos_souls(&data);
			return ;
		}
		pthread_mutex_unlock(&data->philo_head->death_mtx);
		data->philo_head = data->philo_head->next;
	}
	return ;
}
