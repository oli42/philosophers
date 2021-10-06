/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 16:03:40 by ochichep          #+#    #+#             */
/*   Updated: 2021/09/30 13:23:22 by ochichep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"	

int	free_all(t_philo **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		pthread_mutex_destroy(&tab[i]->mutex_fork);
		pthread_mutex_destroy(tab[i]->list.mutex_target);
		pthread_mutex_destroy(tab[i]->list.mutex_status);
		pthread_detach(tab[i]->thread);
		free(tab[i]);
		i++;
	}
	free (tab);
	return (0);
}

static int	check_full_norm(int tag, t_philo **tab, int i)
{
	long long	time;

	time = 0;
	if (tag == tab[i]->list.total_philo && tab[i]->list.total_philo > 1)
	{
		pthread_mutex_lock(tab[i]->list.mutex_status);
		printf("\033[033m%lld ms ### all philisophers ate %d times\033[0m\n" \
		, get_time3(time, tab[i]), tab[i]->list.nbr_lunch);
		return (0);
	}
	else
	{
		pthread_mutex_lock(tab[i]->list.mutex_status);
		printf("\033[0;31m%lld ms - %d died\033[0m\n", \
			get_time3(time, tab[i]), tab[i]->id);
	}
	return (0);
}

int	check_full(void *arg)
{
	int			i;
	t_philo		**tab;

	i = 0;
	tab = (t_philo **)arg;
	while (tab[0]->list.toll < tab[0]->list.total_philo)
	{
		tab[i]->list.toll = 0;
		while (tab[i] != NULL)
		{
			if ((get_time(tab[i]->list.time) - tab[i]->last_lunch) > \
				tab[i]->list.time_to_die)
			{
				tab[i]->list.toll = tab[i]->list.total_philo + 1;
				tab[i]->death = 1;
				check_full_norm(tab[i]->list.toll, tab, i);
				return (0);
			}
			if (tab[i]->full == 1)
				tab[0]->list.toll++;
			i++;
		}
		i = 0;
	}
	check_full_norm(tab[i]->list.toll, tab, i);
	return (0);
}

int	all_in(t_philo **tab_phil)
{
	pthread_t	check_lunch;
	int			i;
	int			j;

	j = 1;
	i = 0;
	start_philo(tab_phil);
	ft_usleep(1);
	j = pthread_create(&check_lunch, NULL, \
		(void *)check_full, (void *)tab_phil);
	if (j != 0)
		return (1);
	if (pthread_join(check_lunch, NULL))
	{
		while (i < tab_phil[0]->list.total_philo)
		{
			j = pthread_join(tab_phil[i]->thread, NULL);
			if (j != 0)
				return (1);
			i++;
		}
		free_all(tab_phil);
	}
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
		if (ok == 1)
		{
			args = parsing(argv);
			usleep(1000);
			tab_phil = create_philo(args);
			usleep(1000);
			init_mutex(tab_phil);
			init_philo(tab_phil);
			all_in(tab_phil);
		}
	}
	return (0);
}
