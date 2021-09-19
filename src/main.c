/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 16:03:40 by ochichep          #+#    #+#             */
/*   Updated: 2021/09/19 12:08:56 by ochichep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"	

int	free_all(t_philo **tab)
{
	int	i;

	i = 1;
	while (tab[i])
	{
		pthread_mutex_destroy(&tab[i]->mutex_fork);
		pthread_mutex_destroy(&tab[i]->mutex_target);
		pthread_mutex_destroy(tab[i]->list.mutex_eval);
		i++;
	}
	i = 1;
	while (i < tab[i]->list.total_philo)
		free(tab[i++]);
	free (tab);
	return (0);
}

int	check_full(void *arg)
{
	int			i;
	t_philo		**tab;
	int			toll;

	i = 1;
	tab = (t_philo **)arg;
	toll = 0;
	while (toll < tab[i]->list.total_philo)
	{
		toll = 0;
		while (tab[i] != NULL)
		{
			if (tab[i]->full == 1)
				toll++;
			if (tab[i]->death == 1)
				toll = tab[i]->list.total_philo + 1;
			i++;
		}
		i = 1;
	}
	check_full_norm(toll, tab);
	return (0);
}

int	check_full_norm(int tag, t_philo **tab)
{
	long long	time;
	int			i;

	time = 0;
	i = 1;
	if (tag == tab[i]->list.total_philo)
	{
		pthread_mutex_lock(tab[i]->list.mutex_eval);
		printf("\033[033m%lld ms ### all philisophers ate %d times\033[0m\n" \
		, get_time(time), tab[i]->list.nbr_lunch);
		return (0);
	}
	else
	{
		pthread_mutex_lock(tab[i]->list.mutex_eval);
		printf("\033[0;31m%lld ms - %d died\033[0m\n", \
			get_time(time), tab[i]->id);
	}
	return (0);
}

int	all_in(t_philo **tab_phil)
{
	pthread_t	check_lunch;
	int			i;
	int			j;

	j = 1;
	i = 1;
	j = pthread_create(&check_lunch, NULL, \
		(void *)check_full, (void *)tab_phil);
	if (j != 0)
		return (1);
	start_philo(tab_phil);
	if (pthread_join(check_lunch, NULL))
	{
		while (i < tab_phil[1]->list.total_philo)
		{
			j = pthread_join(tab_phil[i]->thread, NULL);
			if (j != 0)
				return (1);
			i++;
		}
	}
	free_all(tab_phil);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args		args;
	t_philo		**tab_phil;
	int			ok;

	ok = 1;
	if (argc > 1)
	{
		ok = check_digit(argv);
		if (ok == 0)
			return (0);
		ok = check_sa_race(argv);
		if (ok == 0)
			return (0);
		usleep(100);
		if (ok == 1 || ok == -1)
		{
			args = parsing(argv);
			tab_phil = create_philo(args);
			init_philo(tab_phil);
			init_mutex(tab_phil);
			all_in(tab_phil);
		}
	}
	return (0);
}
