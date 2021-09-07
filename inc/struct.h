/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 10:20:58 by ochichep          #+#    #+#             */
/*   Updated: 2021/09/03 16:18:33 by ochichep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>
# include <string.h>

# define TMA "Too many arguments\n"
# define WA "Wrong arguments\n"
# define TLA "Too long arguments\n"
# define FZ "Zero not allowed\n"

typedef struct s_args {
	int		total_philo;
	int		time_to_eat;
	int		time_to_die;
	int		time_to_sleep;
	int		nbr_lunch;
//	pthread_mutex_t	*mutex_eval;

}				t_args;

typedef struct s_philo {
	pthread_t		thread;
	pthread_mutex_t	mutex_fork;
	pthread_mutex_t	mutex_target;
//	pthread_mutex_t	mutex_status;
	int				flag;
	int				*check_flag;
	int				id;
	long int		start_routine;
	long int		start_eating;
	long int		start_sleeping;
	long int		start_thinking;
	int				ate_lunch;
	long long		last_lunch;
	int				full;
	int				death;
	t_args			list;
}					t_philo;
#endif
