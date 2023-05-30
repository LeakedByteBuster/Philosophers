/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:39:51 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/31 00:23:34 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

// size_t			ft_strlen(char *s);
// unsigned long	get_time_in_ms(struct timeval start);
// inline bool		ft_isdigit(int c);
int				ft_atoi_parser(char *s);
// int				print_err(char *s, int exit_status);

int	init_data_struct(t_data *data, char **av)
{
	memset(data, 0, sizeof(t_data));
	data->nbr_philos = ft_atoi_parser(av[1]);
	if (data->nbr_philos == -1 || data->nbr_philos == 0
		|| data->nbr_philos > 200)
		return (-1);
	data->time_to_die = ft_atoi_parser(av[2]);
	if (data->time_to_die == -1)
		return (-1);
	data->time_to_eat = ft_atoi_parser(av[3]);
	if (data->time_to_eat == -1)
		return (-1);
	data->time_to_sleep = ft_atoi_parser(av[4]);
	if (data->time_to_sleep == -1)
		return (-1);
	if (av[5])
	{	
		data->number_of_meals = ft_atoi_parser(av[5]);
		if (data->number_of_meals == -1)
			return (-1);
	}
	return (0);
}

//	check if the given charachter is digit
inline bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

//	Converts ASCII to integer and parse given string
int		ft_atoi_parser(char *s)
{
	unsigned long	res;

	res = 0;
	if (s[0] == '-')
		return (-1);
	else if (s[0] == '+')
		s++;
	while (s && *s)
	{
		if ((*s >= '0' && *s <= '9') == 0)
			return (-1);
		res = res * 10 + *s++ - '0';
		if (res > INT32_MAX)
			return (-1);
	}
	return (res);
}

// Returns len of s
size_t	ft_strlen(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

//	Prints error in STDERR
int	print_err(char *s, int exit_status)
{
	write(2, s, ft_strlen(s));
	return (exit_status);
}

//	Returns time passed between stop and start in miliseconds
unsigned long	get_time_in_ms(struct timeval start)
{
	struct timeval	stop;

	gettimeofday(&stop, NULL);
	return (((stop.tv_sec - start.tv_sec) * 1000)
		+ ((stop.tv_usec - start.tv_usec) / 1000));
}
