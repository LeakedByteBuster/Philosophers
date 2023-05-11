/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:26:45 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/11 02:46:15 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
// #define NDEBUG

/*
Any state change of a philosopher must be formatted as follows:
	◦timestamp_in_ms X has taken a fork
	◦timestamp_in_ms X is eating
	◦timestamp_in_ms X is sleeping
	◦timestamp_in_ms X is thinking
	◦timestamp_in_ms X died
*/

/*
	void	sleep(nbr_of_ms)
	{
		mutex_lock
		write(is sleeping)
		mutex_unlock
		usleep(ms)
	}
	void	think(nbr_of_ms)
	{
		write(thinking)
	}
	void	eat(nbr_of_ms)
	{
		write(eating)
	}
*/

/*
int	philosophers_birth(philos)
{
	while (nbr_philos)
		pthread_create(&tid, NULL, philosophers_lifecyle(), NULL);
}

*/
// void	*foo(void *i)
// {

// 	return (NULL);
// }

static int	dining_philosophers_routine(t_data *data)
{
	// int philosophers_birth(philos);
	/*
	while (TRUE)
	{
		take_fork(); (left and right)
		eat();
		put_fork(); (left and right)
		sleep();
		think();
		if (time to die)
			set_a_shared variable;
	}
	*/
	(void)data;
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac <= 3 || ac > 6)
		return (print_err(ARGUMENTS_PROTOTYPE, 1));
	if (init_simulation(&data, av) == -1)
		return (print_err("Error in arguments", 1));
	dining_philosophers_routine(&data);

//*************************************************************
		// while (1)
		// 	if (a shared memory == 1)
		// 		a philo has died : simulation ends
	t_philo *head = data.philos;
	int i = -1;
	while (++i < data.nbr_of_philos)
	{
		printf("id = %d | d_or_a = %d | curr_state = %d | my_fork = %d\n", \
		(head->philo_id), head->dead_or_alive, head->curr_state, head->my_fork);
		head = head->next;
	}
//*************************************************************

	clear_list(data.philos, data.nbr_of_philos);	 
	return (0);
}

/*************************************************/

// t_philo *head = data.philos;
// int i = -1;
// while (++i < data.nbr_of_philos)
// {
// 	printf("id = %d | d_or_a = %d | curr_state = %d | my_fork = %d\n", \
	// 	(head->philo_id), head->dead_or_alive, head->curr_state, head->my_fork);
// 	head = head->next;
// }
/*************************************************/
