/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:26:45 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/18 04:21:34 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#define MAX_THREADS 2100
// #define NDEBUG

static int	dining_philosophers_routine(t_philo *philo)
{
	if (philo->philo_id % 2 != 0)
		usleep(1000);
	pthread_mutex_init(&philo->mtx, NULL);
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
	unsigned long	i;

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
