/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 19:26:47 by mfouadi           #+#    #+#             */
/*   Updated: 2023/05/18 05:19:48 by mfouadi          ###   ########.fr       */
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

void	ft_itoa(char *buff, int x)
{
	size_t	len;
	int		tmp;
	int		i;

	len = ft_strlen(buff);
	if (x == 0)
	{
		buff[len++] = (char)'0';
		return ;
	}
	i = 0;
	tmp = x;
	while (tmp)
	{
		tmp /= 10;
		i++;
	}
	while (x)
	{
		buff[len++] = x % 10 + '0';
		x = x / 10;
		i--;
	}
	return ;
}

unsigned long	get_time_in_ms(struct timeval start)
{
	struct timeval stop;
	gettimeofday(&stop, NULL);
	return (((stop.tv_sec - start.tv_sec) * 1000) + ((stop.tv_usec - start.tv_usec) / 1000));
}

size_t	ft_strlcpy(char *dst, char *src, size_t	dstsize)
{	
	size_t	i;
	size_t	srclen;	

	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	i = 0;
	while ((*src != '\0') && (i++ < dstsize - 1))
		*dst++ = *src++;
	*dst = '\0';
	return (srclen);
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_src;
	size_t	len_dst;

	len_src = ft_strlen(src);
	if ((dstsize == 0 && dst == NULL) || dstsize == 0)
		return (len_src);
	len_dst = ft_strlen(dst);
	if (dstsize < len_dst)
		return (dstsize + len_src);
	i = len_dst;
	while (*src && i++ < dstsize - 1)
		*(dst++ + len_dst) = *src++;
	*(dst + len_dst) = '\0';
	return (len_dst + len_src);
}
