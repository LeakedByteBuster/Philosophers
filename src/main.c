/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:26:45 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/19 20:55:07 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#define MAX_THREADS 2100
// #define NDEBUG
// ./philo 5 800 200 200 no one sould die (285123 ms)
// ./philo 4 410 200 200 (346800 ms)
// ./philo 5 310 200 200 (die at time)
// ./philo 2 310 200 200 (consistent delay of 1 - 4ms)
//************************************************************
// .philo 5 800 200 200 7 (sometimes prints less eating)
// ./philo 1 800 200 200 should print if he is alone
// ./philo 0 60 200 200 SEGFAULT
// ./philo 2147483648 410 200 200 SEGFAULT
static void	dining_philosophers_routine(t_philo *philo)
{
	pthread_mutex_init(&philo->mtx, NULL);
	pthread_mutex_init(&philo->death_mtx, NULL);
	unsigned long start_time = get_time_in_ms(philo->start);
	if ((philo->philo_id % 2 != 0) && (philo->data->nbr_of_philos > 1))
	{
		pthread_mutex_lock(&philo->death_mtx);
		while (((get_time_in_ms(philo->start) - start_time) < philo->data->time_to_eat)
			&& (philo->dead_or_alive == 1))
		{
			pthread_mutex_unlock(&philo->death_mtx);
			usleep(100);
			pthread_mutex_lock(&philo->death_mtx);
		}
		if (philo->dead_or_alive == 0)
			return ;
	}
	pthread_mutex_unlock(&philo->death_mtx);
	while (1)
	{
		pthread_mutex_lock(&philo->death_mtx);
		if(philo->dead_or_alive == 0)
			break ;
		pthread_mutex_unlock(&philo->death_mtx);

		if (pick_forks(philo) == -1)
			break ;
		eat(philo);
		put_forks(philo);
		pthread_mutex_lock(&philo->death_mtx);
		if (philo->dead_or_alive == 0)
			break;
		pthread_mutex_unlock(&philo->death_mtx);
		ft_sleep(philo);
		
		if (philo->nbr_of_meals_taken == philo->data->number_of_meals)
			break ;
	}
	pthread_mutex_destroy(&philo->mtx);
	pthread_mutex_destroy(&philo->death_mtx);
	return ;
}

int	main(int ac, char **av)
{
	static t_philo	philo[MAX_THREADS];
	struct timeval start;
	t_data	data;
	int		err;
	unsigned long	i;

//*************************INIT SIMULATION*********************************//
	err = 0;
	if (ac <= 4 || ac > 6)
		return (print_err(PROGRAM_ARGUMENTS_PROTOTYPE, 1));
	if (init_simulation(&data, av) == -1)
		return (print_err("Error in arguments", 1));
	data.simulation = 1;
//****************************INIT MUTEX**************************************//
	pthread_mutex_init(&data.print_mtx, NULL);
	pthread_mutex_init(&data.data_mtx, NULL);
//***************************GET TIME SINCE EPOCH****************************//
	gettimeofday(&start, NULL);
//*****************CREATE CIRCULAR LIKED_LIST & PHILOS************************//
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
//**************************CREATE GRIM_REAPER**************************************//
	pthread_t	grim;
	data.philo_head = &philo[0];
	data.start = start;
	pthread_create(&grim, NULL, (void *)grim_reaper, &data);
//*************************JOIN PHILOS**************************************//
	i = -1;
	while(++i < philo->data->nbr_of_philos)
	{
		if (pthread_join(philo[i].tid, NULL) != 0)
			write(2, "pthread_join", ft_strlen("pthread_join"));
	}
//************************FINISH SIMULATION & DESTROY MUTEXES*****************//

	data.simulation = 0;

//**************************JOIN GRIM_REAPER***********************************//
	pthread_join(grim, NULL);
//******************************PRINT DEATH IF IT WAS************************//
	// printf("====> dead = %d", d)
	if (data.death_id != 0)
		printf("%lu	philo %d has died\n", get_time_in_ms(data.start) ,data.death_id);
	pthread_mutex_destroy(&data.print_mtx);
	pthread_mutex_destroy(&philo->data->data_mtx);
//***************************RETURN *************************************//
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
