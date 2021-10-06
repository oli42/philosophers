/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:40:56 by ochichep          #+#    #+#             */
/*   Updated: 2021/09/30 12:40:40 by ochichep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(long long time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long long goal)
{
	long long	start;
	long long	time;

	start = 0;
	time = 0;
	start = get_time(time);
	while ((get_time(time) - start) <= goal)
		usleep(goal);
}

long long	get_time2(long long time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	time -= (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

long long	get_time3(long long time, t_philo *phil)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	time -= phil->start_routine;
	return (time);
}
