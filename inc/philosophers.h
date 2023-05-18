/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:29:07 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/18 21:08:06 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#define PROGRAM_ARGUMENTS_PROTOTYPE "number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat] (The last argument \
is optional)"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <assert.h>
#include <stdbool.h>

typedef enum t_states
{
	DEAD,
	HUNGRY,
	EATING,
	SLEEPING,
	THINKING
}	s_states;

typedef struct s_philo t_philo;

typedef struct	s_data
{
	pthread_mutex_t print_mtx;
	pthread_mutex_t data_mtx;
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


typedef struct s_philo
{
	pthread_t		tid;
	pthread_mutex_t	mtx;
	pthread_mutex_t death_mtx;
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

int		init_simulation(t_data *data, char **av);
void	free_ptr(pthread_t **p);

bool	ft_isdigit(int c);
void	ft_itoa(char *buff, int x);
int		ft_atoi_parser(char *s);
size_t	ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);


int		print_err(char *s, int exit_status);
char	*ft_strdup(const char *s1);


t_philo *create_and_init_philo(int content);
int		insert_back(t_philo **head, t_philo *new_node);
void	clear_list(t_philo *head, int list_size);

 int right(int i, int n);
int inline left(int i, int n);
int	init_philo_data(t_philo *philo, t_data *data, int i);

unsigned long	get_time_in_ms(struct timeval start);
void	eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
int		pick_forks(t_philo *philo);
void	put_forks(t_philo *philo);

#endif // PHILOSOPHERS_H
