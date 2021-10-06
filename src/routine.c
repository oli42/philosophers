/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 16:04:34 by ochichep          #+#    #+#             */
/*   Updated: 2021/09/30 12:39:37 by ochichep         ###   ########.fr       */
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
			pthread_mutex_lock(&phil->mutex_fork);
		}
	}
	else if (ft_strcmp(str, "time_to_eat") == 0)
	{
		if ((time - phil->start_eating) > (phil->list.time_to_eat))
			phil->death = 1;
	}
	return (0);
}

t_philo	*sleeping(t_philo *phil)
{
	long long	time;

	time = 0;
	pthread_mutex_lock(phil->list.mutex_status);
	printf("%lld ms - %d - is sleeping\n", get_time3(time, phil), phil->id);
	pthread_mutex_unlock(phil->list.mutex_status);
	ft_usleep(phil->list.time_to_sleep);
	pthread_mutex_lock(phil->list.mutex_status);
	printf("%lld ms - %d - is thinking\n", get_time3(time, phil), phil->id);
	pthread_mutex_unlock(phil->list.mutex_status);
	return (phil);
}

void	*routine(void *arg)
{
	t_philo		*phil;
	long long	time;

	time = 0;
	phil = (t_philo *)arg;
	phil->last_lunch = get_time(time);
	phil->start_routine = phil->last_lunch;
	if (phil->id % 2 == 0)
		ft_usleep(phil->list.time_to_eat);
	while (phil)
	{
		handle_fork(phil);
		eating(phil);
		sleeping(phil);
	}
	free(arg);
	return (0);
}

void	init_philo_2(t_philo **tab_phil)
{
	int	i;

	i = 0;
	while (tab_phil[i])
	{
		if (i == tab_phil[0]->list.total_philo - 1)
			tab_phil[i]->check_flag = &tab_phil[0]->flag;
		else
			tab_phil[i]->check_flag = &tab_phil[i + 1]->flag;
		if (tab_phil[i]->list.total_philo == 1)
			tab_phil[i]->list.mutex_target = &tab_phil[0]->mutex_fork;
		else
		{
			if (tab_phil[i]->id == tab_phil[0]->list.total_philo)
				tab_phil[i]->list.mutex_target = &tab_phil[0]->mutex_fork;
			else
				tab_phil[i]->list.mutex_target = &tab_phil[i + 1]->mutex_fork;
		}
		i++;
	}
}
