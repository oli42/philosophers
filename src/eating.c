/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 15:59:30 by ochichep          #+#    #+#             */
/*   Updated: 2021/09/03 17:51:59 by ochichep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *phil)
{
	long long	time;

	time = 0;
	starter(phil, "eating");
	checker(phil, "time_to_die");
	time = get_time(time);
	phil->last_lunch = time;
	phil->ate_lunch++;
//	pthread_mutex_lock(phil->list.mutex_eval);
	printf("%lld ms - %d is eating (\033[0;31m%d\033[0m)\n" \
		, time, phil->id, phil->ate_lunch);
//	pthread_mutex_unlock(phil->list.mutex_eval);
	if (phil->ate_lunch == phil->list.nbr_lunch)
		phil->full = 1;
	while ((time - phil->start_eating) < (phil->list.time_to_eat))
		time = get_time(time);
//	usleep(1000);
}

void	handle_fork(t_philo *phil)
{
	long long	time;

	time = 0;
	while (phil->flag == 1)
		checker(phil, "time_to_die");
	phil->flag = 1;
//	pthread_mutex_lock(phil->list.mutex_eval);
	printf("%lld ms - %d take his fork\n", get_time(time), phil->id);
//	pthread_mutex_unlock(phil->list.mutex_eval);
	pthread_mutex_lock(&phil->mutex_fork);
	while (*phil->check_flag == 1)
		checker(phil, "time_to_die");
	*phil->check_flag = 1;
//	pthread_mutex_lock(phil->list.mutex_eval);
	printf("%lld ms - %d take his second fork\n", get_time(time), phil->id);
//	pthread_mutex_unlock(phil->list.mutex_eval);
	pthread_mutex_lock(&phil->mutex_target);
	eating(phil);
	pthread_mutex_unlock(&phil->mutex_fork);
	phil->flag = 0;
	*phil->check_flag = 0;
	pthread_mutex_unlock(&phil->mutex_target);
	sleeping(phil);
	/* starter(phil, "sleeping");
	pthread_mutex_lock(&phil->list.mutex_eval);
	printf("%lld ms - %d is sleeping\n", get_time(time), phil->id);
	while ((time - phil->start_sleeping) < (phil->list.time_to_sleep))
		time = get_time(time);
	pthread_mutex_unlock(&phil->list.mutex_eval);
//	usleep(1);
	pthread_mutex_lock(&phil->list.mutex_eval);
	printf("%lld ms - %d is thinking\n", time, phil->id);
	pthread_mutex_unlock(&phil->list.mutex_eval);
	usleep(1);		 */

}
