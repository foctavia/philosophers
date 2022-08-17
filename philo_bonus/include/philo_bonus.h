/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:24:45 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/17 10:24:49 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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
# include <semaphore.h>

typedef struct s_philo
{
	int					*dead;
	int					stop;
	unsigned long long	num;
	unsigned long long	last_meal;
	unsigned long long	meal_count;
	pid_t				id;
	struct s_philo		*next;
	struct s_philo		*prev;
	struct s_info		*info;
}				t_philo;

typedef struct s_info
{
	int					dead;
	unsigned long long	philo_num;
	unsigned long long	die_time;
	unsigned long long	eat_time;
	unsigned long long	sleep_time;
	unsigned long long	meal_num;
	sem_t				*print;
	sem_t				*data;
	sem_t				*fork;
	pthread_t			monitor_id;
	t_philo				*philo;
	t_philo				*tmp;
}				t_info;

int					check_meal(t_philo *philo);
int					check_die(t_info *info);
int					check_die_stop(t_philo *philo);
int					err_msg(int err);
int					ft_isdigit(int c);
int					ft_strcmp(char *s1, char *s2);

void				create_info(t_info **info);
void				check_arg(t_info *info, int argc, char **argv);
void				philo_init(t_info *info);
void				simulation(void *arg);
void				*monitor(void *arg);
void				ft_log(t_info *info, int num, char *str);
void				unlink_kill(t_info *info);
void				terminate(t_info *info);
void				unlink_free(t_info *info);
void				err_free(t_info *info, int err);
void				err_kill_free(t_info *info, int err);
void				free_list(t_philo *philo);
void				ft_putstr_fd(char *s, int fd);

char				*ft_itoa_ph(t_info *info, unsigned long long n);

unsigned long long	timestamp(void);
unsigned long long	ft_atoi_ph(t_info *info, const char *str);

#endif
