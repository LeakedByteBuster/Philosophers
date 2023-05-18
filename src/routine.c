/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 03:36:26 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/18 03:52:58 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->death_mtx);
	
	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%lu %d is eating\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mtx);

	unsigned long start_time = get_time_in_ms(philo->start);
	while ((int)(get_time_in_ms(philo->start) - start_time) < philo->data->time_to_eat)
	{
		pthread_mutex_unlock(&philo->death_mtx);
		usleep(10);
		pthread_mutex_lock(&philo->death_mtx);
	}
	// pthread_mutex_lock(philo->death_mtx);
	philo->last_meal = get_time_in_ms(philo->start);
	pthread_mutex_unlock(&philo->death_mtx);
	philo->nbr_of_meals_taken += 1;
	return ;
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->death_mtx);
	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%lu %d is sleeping\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mtx);

	unsigned long	start_time = get_time_in_ms(philo->start);
	while ((int)(get_time_in_ms(philo->start) - start_time) < philo->data->time_to_sleep)
	{
		pthread_mutex_unlock(&philo->death_mtx);
		usleep(10);
		pthread_mutex_lock(&philo->death_mtx);
	}
	pthread_mutex_unlock(&philo->death_mtx);
	return ;
}

void	pick_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	pthread_mutex_lock(&philo->death_mtx);
	printf("%lu %d is thinking\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->death_mtx);
	pthread_mutex_unlock(&philo->data->print_mtx);

	pthread_mutex_lock(&philo->mtx);
	pthread_mutex_lock(&philo->death_mtx);
	printf("%lu %d has taken a fork\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->death_mtx);

	pthread_mutex_lock(&philo->prev->mtx);
	pthread_mutex_lock(&philo->death_mtx);
	printf("%lu %d has taken a fork\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->death_mtx);

	return ;
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->mtx);
	pthread_mutex_unlock(&philo->prev->mtx);
	return ;
}
