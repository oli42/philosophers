/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 15:59:18 by ochichep          #+#    #+#             */
/*   Updated: 2021/08/30 11:48:58 by ochichep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **argv, int i)
{
	if (ft_atoi(argv[i]) <= 0)
	{
		ft_putstr_fd(FZ, 1);
		exit(0);
	}
	if (ft_strlen(argv[i]) > 10)
	{
		ft_putstr_fd(TLA, 1);
		exit(0);
	}
	return (0);
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
				exit(0);
			}
			j++;
		}
		check_args(argv, i);
		if (i > 5)
		{
			ft_putstr_fd(TMA, 1);
			exit(0);
		}
		i++;
	}
	return (0);
}
