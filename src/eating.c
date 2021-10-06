/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 15:59:30 by ochichep          #+#    #+#             */
/*   Updated: 2021/09/30 12:34:35 by ochichep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*eating(t_philo *phil)
{
	long long	time;

	time = 0;
	pthread_mutex_lock(phil->list.mutex_status);
	phil->last_lunch = get_time(time);
	phil->ate_lunch++;
	printf("%lld ms - %d - is eating (\033[0;31m%d\033[0m)\n" \
	, get_time3(time, phil), phil->id, phil->ate_lunch);
	pthread_mutex_unlock(phil->list.mutex_status);
	ft_usleep(phil->list.time_to_eat - ((get_time(time) - phil->last_lunch)));
	pthread_mutex_unlock(&phil->mutex_fork);
	pthread_mutex_unlock(phil->list.mutex_target);
	if (phil->ate_lunch == phil->list.nbr_lunch)
		phil->full = 1;
	return (phil);
}

t_philo	*handle_fork_2(t_philo *phil)
{
	long long	time;

	time = 0;
	pthread_mutex_lock(phil->list.mutex_target);
	pthread_mutex_lock(phil->list.mutex_status);
	printf("%lld ms - %d - take his second fork\n", \
		get_time3(time, phil), phil->id);
	pthread_mutex_unlock(phil->list.mutex_status);
	return (phil);
}

t_philo	*handle_fork(t_philo *phil)
{
	long long	time;

	time = 0;
	pthread_mutex_lock(&phil->mutex_fork);
	pthread_mutex_lock(phil->list.mutex_status);
	printf("%lld ms - %d - take his fork\n", get_time3(time, phil), phil->id);
	pthread_mutex_unlock(phil->list.mutex_status);
	handle_fork_2(phil);
	return (phil);
}
