/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 15:59:18 by ochichep          #+#    #+#             */
/*   Updated: 2021/09/19 11:19:12 by ochichep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **argv, int i)
{
	if (ft_atoi(argv[i]) <= 0)
	{
		ft_putstr_fd(FZ, 1);
		return (0);
	}
	if (ft_strlen(argv[i]) > 10)
	{
		ft_putstr_fd(TLA, 1);
		return (0);
	}
	return (1);
}

int	check_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				ft_putstr_fd(WA, 1);
				return (0);
			}
			j++;
		}	
		i++;
	}
	return (1);
}

int	check_sa_race(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (argv[i])
	{
		j = check_args(argv, i);
		if (j == 0)
			return (0);
		i++;
	}
	if (i < 5 || i > 6)
	{
		ft_putstr_fd(TMA, 1);
		return (0);
	}
	return (j);
}
