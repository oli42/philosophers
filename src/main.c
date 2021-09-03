/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 16:03:40 by ochichep          #+#    #+#             */
/*   Updated: 2021/08/30 18:00:33 by ochichep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"	

int	check_full_norm(int i, t_philo **tab, void *arg)
{
	long long	time;
	int			toll;

	time = 0;
	toll = 0;
	while (toll != tab[i]->list.total_philo)
	{
		toll = 0;
		while (tab[i] != NULL)
		{
			if (tab[i]->full == 1)
				toll++;
			if (tab[i]->death == 1)
			{
				time = get_time(time);
				printf("\033[0;31m%lld ms, %d died\033[0m\n", time, tab[i]->id);
				free(arg);
				exit(0);
			}
			i++;
		}
		i = 1;
	}
	return (0);
}

void	*check_full(void *arg)
{
	int			i;
	long long	time;
	t_philo		**tab;

	i = 1;
	time = 0;
	tab = (t_philo **)arg;
	check_full_norm(i, tab, arg);
	time = get_time(time);
	pthread_mutex_lock(&tab[i]->mutex_status);
	printf("\033[033m%lld ms ### all philisophers ate %d times\033[0m\n" \
		, time, tab[i]->list.nbr_lunch);
	free(arg);
	exit(0);
}

int	all_in(t_philo **tab_phil)
{
	pthread_t	check_lunch;
	int			i;
	int			j;

	j = 1;
	j = pthread_create(&check_lunch, NULL, &check_full, (void *)tab_phil);
	if (j != 0)
		return (1);
	start_philo(tab_phil);
	i = 1;
	j = pthread_join(check_lunch, NULL);
	if (j != 0)
		return (1);
	while (i < tab_phil[1]->list.total_philo)
	{
		j = pthread_join(tab_phil[i]->thread, NULL);
		if (j != 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_args		args;
	t_philo		**tab_phil;

	if (argc > 1)
	{
		check_digit(argv);
		usleep(1000);
		args = parsing(argv);
		tab_phil = create_philo(args);
		init_philo(tab_phil);
		init_mutex(tab_phil);
		all_in(tab_phil);
	}
	return (0);
}
