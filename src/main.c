/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:26:45 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/15 16:38:02 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#define MAX_THREADS 2100
// #define NDEBUG

unsigned long	get_time_in_ms(struct timeval start)
{
	struct timeval stop;
	gettimeofday(&stop, NULL);
	return (((stop.tv_sec - start.tv_sec) * 1000) + ((stop.tv_usec - start.tv_usec) / 1000));
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%lu %d is eating\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mtx);
	usleep(philo->data->time_to_eat);
	philo->last_meal = get_time_in_ms(philo->start);
	philo->nbr_of_meals_taken += 1;
	return ;
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%lu %d is sleeping\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mtx);
	usleep(philo->data->time_to_sleep);
	return ;
}

void	pick_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%lu %d is thinking\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mtx);

	pthread_mutex_lock(&philo->mtx);
	printf("%lu %d has taken a fork\n", get_time_in_ms(philo->start), philo->philo_id);

	pthread_mutex_lock(&philo->prev->mtx);
	printf("%lu %d has taken a fork\n", get_time_in_ms(philo->start), philo->philo_id);
	return ;
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->mtx);
	pthread_mutex_unlock(&philo->prev->mtx);
	return ;
}

static int	dining_philosophers_routine(t_philo *philo)
{
	pthread_mutex_init(&philo->mtx, NULL);
	// if ((philo->philo_id % 2) == 0)
	// 	usleep(100);
	while (1)
	{
		pick_forks(philo);
		eat(philo);
		put_forks(philo);
		if (philo->nbr_of_meals_taken == philo->data->number_of_meals)
			break;
		ft_sleep(philo);
	}
	pthread_mutex_destroy(&philo->mtx);
	return (0);
}

int	main(int ac, char **av)
{
	static t_philo	philo[MAX_THREADS];
	struct timeval start;
	t_data	data;
	int		err;
	int		i;

	err = 0;
	if (ac <= 4 || ac > 6)
		return (print_err(PROGRAM_ARGUMENTS_PROTOTYPE, 1));
	if (init_simulation(&data, av) == -1)
		return (print_err("Error in arguments", 1));

	pthread_mutex_init(&data.print_mtx, NULL);
	gettimeofday(&start, NULL);
	i = -1;
	while (++i < data.nbr_of_philos)
	{
		init_philo_data(&philo[i], &data, i);
		philo[i].start = start;
		philo[i].next = &philo[((i + 1) % data.nbr_of_philos)];
		philo[i].prev = &philo[((i - 1 + data.nbr_of_philos) % data.nbr_of_philos)];
		if (pthread_create(&philo[i].tid, NULL, (void *)dining_philosophers_routine, &philo[i]) != 0)
			return (-1);
	}
	assert(i == data.nbr_of_philos);

	i = -1;
	while(++i < philo->data->nbr_of_philos)
		if (pthread_join(philo[i].tid, NULL) != 0)
			write(2, "pthread_join", ft_strlen("pthread_join"));
	return (0);
}

/********************PRINT************************/

// t_philo *head = data.philos;
// int i = -1;
// while (++i < data.nbr_of_philos)
// {
// 	printf("id = %d | d_or_a = %d | curr_state = %d | my_fork = %d\n", \
	// 	(head->philo_id), head->dead_or_alive, head->curr_state, head->my_fork);
// 	head = head->next;
// }
