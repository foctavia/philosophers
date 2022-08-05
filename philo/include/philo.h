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
	uint64_t		num;
	uint64_t		last_meal;
	uint64_t		meal_count;
	pthread_t		*id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_philo	*next;
	struct s_philo	*prev;
}				t_philo;

typedef struct s_info
{
	int				err;
	uint64_t		philo_num;
	uint64_t		die_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	uint64_t		meal_num;
	uint64_t		time;
	pthread_mutex_t	*print;
	t_philo			*philo;
	t_philo			*tmp;
}				t_info;

int	create_info(t_info **info);
int check_arg(t_info *info, int argc, char **argv);
int	err_msg(int err);
int	return_free(t_info *info, int err);
void	end_free(t_info *info);
pthread_mutex_t	**create_fork(t_info *info, pthread_mutex_t **fork);
t_philo	*create_philo(t_info *info, t_philo *philo);

void	ft_putstr_fd(char *s, int fd);
int	ft_isdigit(int c);
int	ft_strcmp(char *s1, char *s2);
char	*ft_itoa_ph(t_info *info, unsigned long long n);
unsigned long long	ft_atoi_ph(t_info *info, const char *str);

#endif

