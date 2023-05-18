/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:26:45 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/19 00:32:55 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#define MAX_THREADS 2100
// #define NDEBUG

static int	dining_philosophers_routine(t_philo *philo)
{
	pthread_mutex_init(&philo->mtx, NULL);
	pthread_mutex_init(&philo->death_mtx, NULL);
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
	return (0);
}

void	grim_reaper(t_data *data)
{
	unsigned long	i = 0;

	while (1 && data->simulation)
	{
		pthread_mutex_lock(&data->philo_head->death_mtx);
		if ((get_time_in_ms(data->start) - data->philo_head->last_meal) > data->time_to_die)
		{
			pthread_mutex_unlock(&data->philo_head->death_mtx);
			data->death_id = data->philo_head->philo_id;
			while (i < data->nbr_of_philos)
			{
				pthread_mutex_lock(&data->philo_head->death_mtx);
				data->philo_head->dead_or_alive = 0;
				pthread_mutex_unlock(&data->philo_head->death_mtx);
				data->philo_head = data->philo_head->next;
				i++;
			}
			return;
		}
		pthread_mutex_unlock(&data->philo_head->death_mtx);
		data->philo_head = data->philo_head->next;
	}
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
