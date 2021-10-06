/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 16:02:58 by ochichep          #+#    #+#             */
/*   Updated: 2021/09/24 13:21:20 by ochichep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *ptr)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ptr[i] == ' ' || ptr[i] == '\r' || ptr[i] == '\t' || ptr[i] == '\n'
		|| ptr[i] == '\v' || ptr[i] == '\f' || ptr[i] == '\r')
		i++;
	if (ptr[i] == '-')
		sign *= -1;
	if (ptr[i] == '-' || ptr[i] == '+')
		i++;
	while (ptr[i] && ptr[i] >= '0' && ptr[i] <= '9')
	{
		if (result * sign > 2147483647)
			return (-1);
		else if (result * sign < -2147483648 || !(ptr))
			return (0);
		else
			result = result * 10 + (ptr[i] - '0');
		i++;
	}
	return (result * sign);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			write(fd, &str[i], 1);
			i++;
		}
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if ((s1[i] != '\0' && s2[i] == '\0') || (s1[i] == '\0' && s2[i] != '\0'))
		return (s1[i] - s2[i]);
	return (0);
}
/*
long long	get_time(long long time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	time -= 1632290789999;
	return (time);
}*/
