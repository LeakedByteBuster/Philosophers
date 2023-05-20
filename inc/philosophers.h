/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:29:07 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/20 05:17:42 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define PROGRAM_ARGUMENTS_PROTOTYPE "\033[1;37m ./philo \033[1;30m number_of_\
philosophers \033[1;31m time_to_die \033[1;32m time_to_eat \033[1;34m time_to_\
sleep \033[1;36m [number_of_times_each_philosopher_must_eat] \033[1;33m \
(The last argument is optional)\033[0m\n"
# define ARGUMENT_ERROR "Error in arguments \n\033[1;31m[ Max philosophers is \
200 \033[1;37m & \033[1;31m Acceptable range of numbers is from 0 up to INT64_\
MAX ]\033[0m\n"

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <assert.h>
# include <stdbool.h>

typedef enum t_states
{
	DEAD,
	ALIVE,
	HUNGRY,
	EATING,
	SLEEPING,
	THINKING
}	t_states;

typedef struct s_philo	t_philo;

/* ************************************************************************** */
/*							General data									  */
/* ************************************************************************** */
typedef struct s_data
{
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	data_mtx;
	t_philo			*philo_head;
	struct timeval	start;
	unsigned long	nbr_of_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	number_of_meals;
	int				simulation;
	int				death_id;
}	t_data;

/* ************************************************************************** */
/*							data of each philo								  */
/* ************************************************************************** */
typedef struct s_philo
{
	pthread_t		tid;
	pthread_mutex_t	mtx;
	pthread_mutex_t	death_mtx;
	unsigned long	philo_id;
	unsigned long	dead_or_alive;
	unsigned long	fork;
	unsigned long	last_meal;
	unsigned long	nbr_of_meals_taken;
	struct timeval	start;
	t_data			*data;
	struct s_philo	*next;
	struct s_philo	*prev;
}	t_philo;

/* ************************************************************************** */
/*							Used for parsing								  */
/* ************************************************************************** */
unsigned long	ft_atoi_parser(char *s);
size_t			ft_strlen(char *s);
int				init_simulation(t_data *data, char **av);
int				print_err(char *s, int exit_status);
int				init_philo_data(t_philo *philo, t_data *data, int i);
bool			ft_isdigit(int c);

/* ************************************************************************** */
/*							Used for simulation								  */
/* ************************************************************************** */
unsigned long	get_time_in_ms(struct timeval start);
int				pick_forks(t_philo *philo);
void			eat(t_philo *philo);
void			ft_sleep(t_philo *philo);
void			put_forks(t_philo *philo);
void			grim_reaper(t_data *data);
void			take_philo_soul(t_data **data);

#endif // PHILOSOPHERS_H
