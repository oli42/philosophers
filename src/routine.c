/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 16:04:34 by ochichep          #+#    #+#             */
/*   Updated: 2021/09/03 16:23:54 by ochichep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	starter(t_philo *phil, char *str)
{
	long long	time;

	time = 0;
	time = get_time(time);
	if (ft_strcmp(str, "routine") == 0)
		phil->start_routine = time;
	if (ft_strcmp(str, "eating") == 0)
		phil->start_eating = time;
	if (ft_strcmp(str, "sleeping") == 0)
		phil->start_sleeping = time;
	if (ft_strcmp(str, "thinking") == 0)
		phil->start_thinking = time;
}

int	checker(t_philo *phil, char *str)
{
	long long	time;

	time = 0;
	time = get_time(time);
	if (ft_strcmp(str, "time_to_die") == 0)
	{
		if ((time - phil->last_lunch) > (phil->list.time_to_die))
		{
			phil->death = 1;
		//	pthread_mutex_lock(phil->list.mutex_eval);
		}
	}
	else if (ft_strcmp(str, "time_to_eat") == 0)
	{
		if ((time - phil->start_eating) > (phil->list.time_to_eat))
			phil->death = 1;
	}
	else if (ft_strcmp(str, "sleeping") == 0)
	{
		if ((time - phil->start_sleeping) > (phil->list.time_to_sleep))
			phil->death = 1;
		return (0);
	}
	return (0);
}

void	sleeping(t_philo *phil)
{
	long long	time;

	time = 0;
	starter(phil, "sleeping");
	time = get_time(time);
//	pthread_mutex_lock(phil->list.mutex_eval);
	printf("%lld ms - %d is sleeping\n", time, phil->id);
//	pthread_mutex_unlock(phil->list.mutex_eval);
	while ((time - phil->start_sleeping) < (phil->list.time_to_sleep))
	{
		if (time - phil->last_lunch > phil->list.time_to_die)
			phil->death = 1;
		time = get_time(time);
	}
//	pthread_mutex_lock(phil->list.mutex_eval);
	printf("%lld ms - %d is thinking\n", time, phil->id);
//	pthread_mutex_unlock(phil->list.mutex_eval);
//	usleep(500);

}

void	*routine(void *arg)
{
	t_philo		*phil;
	long long	time;

	time = 0;
	phil = (t_philo *)arg;
	phil->last_lunch = get_time(time);
	while (phil)
	{
		handle_fork(phil);
	}
	free(arg);
	exit(0);
}
