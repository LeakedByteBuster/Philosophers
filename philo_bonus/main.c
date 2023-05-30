/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:06:58 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/31 00:22:53 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac <= 4 || ac > 6)
		return (print_err(PROGRAM_ARGUMENTS_PROTOTYPE, 1));
	if (init_data_struct(&data, av) == -1)
		return (print_err(ARGUMENT_ERROR, 1));
	(void)ac;
	return (0);
}

	// sem_t	forks;
	// pid_t	pid;

	// if (sem_open("forks", O_CREAT | O_EXCL, 0664, 0) == SEM_FAILED)
	// 	return(perror("sem_open "), 2);
	// pid = fork();
	// if (pid == 0)
	// {
	// 	sem_wait(&forks);
	// 	printf("Second\n");
	// 	sem_post(&forks);
	// 	return (0);
	// }
	// printf("First\n");
	// sem_post(&forks);
	// waitpid(pid, NULL, 0);
	// printf("Third\n");
	// sem_close(&forks);
	// sem_unlink("forks");
