/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:39:28 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/31 00:23:24 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
#define PHILOSOPHERS_BONUS_H

# define PROGRAM_ARGUMENTS_PROTOTYPE "\033[1;37m ./philo \033[1;30m number_of_\
philosophers \033[1;31m time_to_die \033[1;32m time_to_eat \033[1;34m time_to_\
sleep \033[1;36m [number_of_times_each_philosopher_must_eat] \033[1;33m \
(The last argument is optional)\033[0m\n"
# define ARGUMENT_ERROR "Error in arguments \n\033[1;31m[ Max philosophers is \
200 \033[1;37m & \033[1;31m Acceptable range of numbers is from 0 up to INT64_\
MAX ]\033[0m\n"

//	* sem_open(), sem_wait(), sem_post(), sem_unlink(), sem,close()
# include <semaphore.h>
//	* waitpid()
# include <sys/wait.h>
// * getimeofday()
# include <sys/time.h>
//	* perror()
# include <stdio.h>
//	* fork()
# include <unistd.h>
//	* datatype `bool`
# include <stdbool.h>
//	* memset()
# include <string.h>

typedef struct s_data
{
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_die;
	int	nbr_philos;
	int number_of_meals;
}	t_data;

// size_t			ft_strlen(char *s);
// unsigned long	get_time_in_ms(struct timeval start);
// int				ft_atoi_parser(char *s);
int				init_data_struct(t_data *data, char **av);
int				print_err(char *s, int exit_status);

// int				print_err(char *s, int exit_status);
// inline bool		ft_isdigit(int c);

#endif // PHILOSOPHERS_H
