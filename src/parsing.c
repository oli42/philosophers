/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 16:04:01 by ochichep          #+#    #+#             */
/*   Updated: 2021/09/03 18:00:56 by ochichep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_args	parsing(char **argv)
{
	int		i;
	t_args	args;

	i = 1;
	while (argv[i])
	{
		args.total_philo = ft_atoi(argv[1]);
		args.time_to_die = ft_atoi(argv[2]);
		args.time_to_eat = ft_atoi(argv[3]);
		args.time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			args.nbr_lunch = ft_atoi(argv[5]);
		i++;
	}
//	args.mutex_eval = (pthread_mutex_t *)malloc(sizeof(args.mutex_eval));
	return (args);
}

t_philo	**create_philo(t_args args)
{
	t_philo	**tab_phil;
	int		i;

	i = 1;
	tab_phil = malloc(sizeof(t_philo) * (args.total_philo));
	while (i <= args.total_philo)
	{
		tab_phil[i] = malloc(sizeof(t_philo));
		tab_phil[i]->list = args;
		tab_phil[i]->id = i;
		i++;
	}
	return (tab_phil);
}

void	init_philo(t_philo **tab_phil)
{
	int	i;

	i = 1;
	while (tab_phil[i])
	{
		tab_phil[i]->start_routine = 0;
		tab_phil[i]->start_eating = 0;
		tab_phil[i]->start_sleeping = 0;
		tab_phil[i]->start_thinking = 0;
		tab_phil[i]->ate_lunch = 0;
		tab_phil[i]->full = 0;
		tab_phil[i]->death = 0;
		tab_phil[i]->flag = 0;
		if (i == tab_phil[1]->list.total_philo)
			tab_phil[i]->check_flag = &tab_phil[1]->flag;
		else
			tab_phil[i]->check_flag = &tab_phil[i + 1]->flag;
		if (i == tab_phil[1]->list.total_philo)
			tab_phil[i]->mutex_target = tab_phil[1]->mutex_fork;
		else
			tab_phil[i]->mutex_target = tab_phil[i + 1]->mutex_fork;
		i++;
	}
}

void	init_mutex(t_philo **tab_phil)
{
	int	i;

	i = 1;
	while (tab_phil[i])
	{
		pthread_mutex_init(&tab_phil[i]->mutex_fork, NULL);
		pthread_mutex_init(&tab_phil[i]->mutex_target, NULL);
	//	pthread_mutex_init(tab_phil[i]->list.mutex_eval, NULL);
		i++;
	}
}

int	start_philo(t_philo **tab_phil)
{
	int			i;
	int			j;

	i = 1;
	j = 1;
	while (i <= tab_phil[1]->list.total_philo)
	{
		j = pthread_create(&tab_phil[i]->thread, NULL, &routine, \
			(void *)tab_phil[i]);
		if (j != 0)
			return (1);
		usleep(67);
		i++;
	}
	return (0);
}
