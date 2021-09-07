/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 17:24:19 by ochichep          #+#    #+#             */
/*   Updated: 2021/08/30 18:35:21 by ochichep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "struct.h"

int				ft_atoi(const char *ptr);
int				check_args(char **argv, int i);
int				check_digit(char **argv);
t_args			parsing(char **argv);
t_philo			**create_philo(t_args args);
void			init_philo(t_philo **tab_phil);
void			init_mutex(t_philo **tab_phil);
int				all_in(t_philo **tab_phil);
int				start_philo(t_philo **tab_phil);
void			*routine(void *arg);
long long		get_time(long long time);
void			starter(t_philo *phil, char *str);
int				checker(t_philo *phil, char *str);
void			handle_fork(t_philo *phil);
int 		    check_full(void *arg);
int 	        check_death(void *arg);
void			eating(t_philo *phil);
void			sleeping(t_philo *phil);
void			ft_putstr_fd(char *str, int fd);
size_t			ft_strlen(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
#endif
