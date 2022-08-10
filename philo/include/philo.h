/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:13:46 by foctavia          #+#    #+#             */
/*   Updated: 2022/07/25 15:14:04 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo
{
	int					dead;
	int					stop;
	unsigned long long	num;
	unsigned long long	last_meal;
	unsigned long long	meal_count;
	pthread_t			id;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
	struct s_philo		*next;
	struct s_philo		*prev;
	struct s_info		*info;
}				t_philo;

typedef struct s_info
{
	int					err;
	unsigned long long	philo_num;
	unsigned long long	die_time;
	unsigned long long	eat_time;
	unsigned long long	sleep_time;
	unsigned long long	meal_num;
	unsigned long long	time;
	pthread_mutex_t		print;
	t_philo				*philo;
	t_philo				*tmp;
}				t_info;

int					create_info(t_info **info);
int					check_arg(t_info *info, int argc, char **argv);
int					philo_init(t_info *info);
int					meal_count(t_philo *philo);
int					err_msg(int err);
int					return_free(t_info *info, int err);
int					ft_isdigit(int c);
int					ft_strcmp(char *s1, char *s2);

void				*simulation(void *arg);
void				*monitor(void *arg);
void				ft_log(t_info *info, int num, char *str);
void				end_free(t_info *info);
void				free_list(t_philo *philo);
void				ft_putstr_fd(char *s, int fd);

t_philo				*create_philo(t_info *info, t_philo *philo);

char				*ft_itoa_ph(t_info *info, unsigned long long n);

unsigned long long 	timestamp(t_info *info);
unsigned long long	ft_atoi_ph(t_info *info, const char *str);

#endif
