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
	int				philo_id;
	int				last_eat;
	pthread_t		*th;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_philo	*next;
}				t_philo;

typedef struct s_info
{
	int				err;
	int				philo_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_num;
	pthread_mutex_t	**fork;
	t_philo			*philo;
}				t_info;

int	info_init(t_info **info);
int	check_parse(t_info *info, int argc, char **argv);
int	err_msg(char *str, int err);
int	return_free(t_info *info, char *str, int err);
void	end_free(t_info *info);

void	ft_putstr_fd(char *s, int fd);
int	ft_isdigit(int c);
unsigned long long	ft_atoi_ph(t_info *info, const char *str);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);

#endif

