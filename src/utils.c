/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:26:47 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/11 01:35:24 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

inline bool	ft_isdigit(int c)
{
	return(c >= '0' && c <= '9');
}

void	free_ptr(pthread_t **p)
{
	int	i;

	if (!p)
		return ;
	i = -1;
	while (p[++i])
		free(p[i]);
	free(p);
}

int	ft_atoi_parser(char *s)
{
	int res = 0;

	if (s[0] == '-')
		return (-1);
	else if (s[0] == '+')
		s++;
	while (s && *s)
	{
		if (ft_isdigit(*s) == 0)
			return (-1);
		res = res * 10 + *s++ - '0';
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

char	*ft_strdup(const char *s1)
{
	char	*ptr1;
	size_t	s1_len;

	s1_len = ft_strlen((char *)s1);
	ptr1 = (char *)malloc(s1_len + 1);
	if (ptr1 == (void *)0)
		return (ptr1);
	while (*s1 != '\0')
		*ptr1++ = *s1++;
	*ptr1 = '\0';
	return (ptr1 - s1_len);
}
