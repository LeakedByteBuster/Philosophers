/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:26:45 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/11 23:04:53 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
// #define NDEBUG

unsigned long	get_time_in_ms(struct timeval start)
{
	struct timeval stop;
	gettimeofday(&stop, NULL);
	return (((stop.tv_sec - start.tv_sec) * 1000) + ((stop.tv_usec - start.tv_usec) / 1000));
}

void	eat(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%lu %d is eating\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mtx);
	usleep(philo->data->time_to_eat);
	philo->last_meal = get_time_in_ms(philo->start);
	return ;
}

void	ft_sleep(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%lu %d is sleeping\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mtx);
	usleep(philo->data->time_to_sleep);
	return ;
}

void	pick_forks(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%lu %d is thinking\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mtx);

	pthread_mutex_lock(&philo->data->fork_mtx);
	printf("%lu %d has taken a fork\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->data->fork_mtx);

	pthread_mutex_lock(&philo->data->fork_mtx);
	printf("%lu %d has taken a fork\n", get_time_in_ms(philo->start), philo->philo_id);
	pthread_mutex_unlock(&philo->data->fork_mtx);

	return ;
}

static int	dining_philosophers_routine(t_philo_data *philo)
{
	pthread_mutex_init(&philo->data->fork_mtx, NULL);
	while (1)
	{
		pick_forks(philo);
		eat(philo);
		// put_fork(); (left and right)
		ft_sleep(philo);
	}
	pthread_mutex_destroy(&philo->data->fork_mtx);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_data	data;
	int		err;
	int		i;

	err = 0;
	if (ac <= 4 || ac > 6)
		return (print_err(PROGRAM_ARGUMENTS_PROTOTYPE, 1));

	err = init_simulation(&data, av);
	if (err == -1)
		return (print_err("Error in arguments", 1));

	i = -1;
	philo = data.philos;
	t_philo_data	philo_data[2100];
	struct timeval start;

	pthread_mutex_init(&data.print_mtx, NULL);
	gettimeofday(&start, NULL);
	while (++i < data.nbr_of_philos)
	{
		philo_data[i].start = start;
		philo_data[i].data = &data;
		philo_data[i].philo_id = i+1;
		if (pthread_create(&philo->tid, NULL, (void *)dining_philosophers_routine, &philo_data[i]) == -1)
			return (-1);
	}
	assert(i == data.nbr_of_philos);
	while (1)
	{
		sleep(10);
		break;
	}
	pthread_mutex_destroy(&data.print_mtx);

	clear_list(data.philos, data.nbr_of_philos);

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
/*************************************************/

	// static void fill_philo_buff(t_philo_data *philo, int id)
	// {
	// 	memset(philo->buff_eating, 0, sizeof(philo->buff_eating));
	// 	memset(philo->buff_sleeping, 0, sizeof(philo->buff_sleeping));
	// 	memset(philo->buff_thinking, 0, sizeof(philo->buff_thinking));
	// 	memset(philo->has_taken_a_fork, 0, sizeof(philo->has_taken_a_fork));

	// 	ft_strlcpy(philo->buff_eating, "timestamp_in_ms ", 17);
	// 	ft_strlcpy(philo->buff_sleeping, "timestamp_in_ms ", 17);
	// 	ft_strlcpy(philo->buff_thinking, "timestamp_in_ms ", 17);
	// 	ft_strlcpy(philo->has_taken_a_fork, "timestamp_in_ms ", 17);
	// 	ft_itoa(philo->buff_eating, id);
	// 	ft_itoa(philo->buff_sleeping, id);
	// 	ft_itoa(philo->buff_thinking, id);
	// 	ft_itoa(philo->has_taken_a_fork, id);
	// 	ft_strl(philo->buff_eating, " is eating\n", 12);
	// 	ft_strl(philo->buff_sleeping, " is sleeping\n", 14);
	// 	ft_strl(philo->buff_thinking, " is thinking\n", 14);
	// 	ft_strl(philo->has_taken_a_fork, " has taken a fork\n", 19);
	// 	philo->philo_id = id;
	// 	return ;
	// }
