/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:26:47 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/20 03:40:16 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

inline bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

unsigned long	ft_atoi_parser(char *s)
{
	unsigned long	res;

	res = 0;
	if (s[0] == '-')
		return (-1);
	else if (s[0] == '+')
		s++;
	while (s && *s)
	{
		if (ft_isdigit(*s) == 0)
			return (-1);
		res = res * 10 + *s++ - '0';
		if (res > INT32_MAX)
			return (-1);
	}
	return (res);
}

size_t	ft_strlen(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

int	print_err(char *s, int exit_status)
{
	write(2, s, ft_strlen(s));
	return (exit_status);
}

unsigned long	get_time_in_ms(struct timeval start)
{
	struct timeval	stop;

	gettimeofday(&stop, NULL);
	return (((stop.tv_sec - start.tv_sec) * 1000)
		+ ((stop.tv_usec - start.tv_usec) / 1000));
}
