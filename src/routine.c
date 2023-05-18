/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 03:36:26 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/18 04:25:11 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%lu %lu is eating\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mtx);

	unsigned long start_time = get_time_in_ms(philo->start);
	while (get_time_in_ms(philo->start) - start_time < philo->data->time_to_eat)
		usleep(10);
	philo->last_meal = get_time_in_ms(philo->start);

	philo->nbr_of_meals_taken += 1;
	return ;
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%lu %lu is sleeping\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mtx);
	
	unsigned long	start_time = get_time_in_ms(philo->start);
	while (get_time_in_ms(philo->start) - start_time < philo->data->time_to_sleep)
		usleep(10);
	return ;
}

void	pick_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%lu %lu is thinking\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mtx);

	pthread_mutex_lock(&philo->prev->mtx);
	printf("%lu %lu has taken a fork\n", get_time_in_ms(philo->start), philo->philo_id);

	pthread_mutex_lock(&philo->mtx);
	printf("%lu %lu has taken a fork\n", get_time_in_ms(philo->start), philo->philo_id);

	return ;
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->mtx);
	pthread_mutex_unlock(&philo->prev->mtx);
	return ;
}
