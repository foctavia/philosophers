/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:14:28 by foctavia          #+#    #+#             */
/*   Updated: 2022/07/25 15:14:38 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_msg(char *str, int err)
{
	if (err == 0)
		ft_putstr_fd(str, 2);
	else
	{
		ft_putstr_fd(str, 2);
		free(str);
	}
	return (1);
}

int	return_free(t_info *info, char *str, int err)
{
	if (info)
	{
		if (info->fork)
			free(info->fork);
		if (info->philo)
			free(info->philo);
		free(info);
	}
	return (err_msg(str, err));
}

void	end_free(t_info *info)
{
	if (info)
	{
		if (info->fork)
			free(info->fork);
		if (info->philo)
			free(info->philo);
		free(info);
	}
}

int	info_init(t_info **info)
{
	*info = (t_info *) malloc(sizeof(t_info));
	if (!(*info))
		return (err_msg("philo: Insufficient memory\n", 0));
	(*info)->err = 0;
	(*info)->philo_num = 0;
	(*info)->die_time = 0;
	(*info)->eat_time = 0;
	(*info)->sleep_time = 0;
	(*info)->eat_num = 0;
	(*info)->fork = NULL;
	(*info)->philo = NULL;
	return (0);
}

int	check_arg(t_info *info, int argc, char **argv)
{
	int	i;
	int	j;
	unsigned long long	num;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (return_free(info, ft_strjoin(argv[i], ": Invalid type of argument\n"), 1));
			j++;
		}
		num = ft_atoi_ph(info, argv[i]);
		if (num > INT_MAX)
			return (return_free(info, ft_strjoin(argv[i], ": Invalid argument values\n"), 1));
		i++;
	}
	return (0);
}

int	parse_arg(t_info *info, int argc, char **argv)
{
	info->philo_num = ft_atoi_ph(info, argv[1]);
	info->die_time = ft_atoi_ph(info, argv[2]);
	info->eat_time = ft_atoi_ph(info, argv[3]);
	info->sleep_time = ft_atoi_ph(info, argv[4]);
	if (argc == 6)
		info->eat_num = ft_atoi_ph(info, argv[5]);
	if (info->err)
		return (return_free(info, "philo: Atoi function error\n", 0));
	if (info->philo_num < 1)
		return (return_free(info, "philo: Invalid number of philosoper\n", 0));
	return (0);
}

void	add_philo(t_philo **ph1, t_philo *ph2)
{
	t_philo	*tmp;

	if (*ph1 == NULL)
	{
		*ph1 = ph2;
		return ;
	}
	tmp = *ph1;
	while (tmp->next != *ph1)
		tmp = tmp->next;
	tmp->next = ph2;
	ph2->next = *ph1;
}

t_philo	*create_philo(t_info *info, t_philo *philo)
{
	t_philo	*tmp;
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		tmp = (t_philo *) malloc(sizeof(t_philo));
		if (!tmp)
		{
			return_free(info, "philo: Insufficient memory\n", 0);
			return (NULL);
		}
		tmp->philo_id = i + 1;
		tmp->last_eat = 0;
		tmp->th = NULL;
		tmp->left_fork = NULL;
		tmp->right_fork = NULL;
		tmp->next = tmp;
		add_philo(&philo, tmp);
		tmp = NULL;
		i++;
	}
	return (philo);
}

// void	*routine()
// {
// 	pthread_mutex_lock(&mutex_philo);

// 	pthread_mutex_unlock(&mutex_philo);
// }

// void	philo(t_tool *tool)
// {
// 	int	i;

// 	tool->th = (pthread_t *)malloc(sizeof(pthread_t * tool->philo_num));
// 	if (!(tool->th))
// 		exit_free(tool, "malloc", 1);
// 	pthread_mutex_init(tool->&mutex_philo, NULL);
// 	i = 0;
// 	while (i < tool->philo_num)
// 	{
// 		pthread_create(tool->&th[i], NULL, &routine, NULL);
// 	}
// 	i = 0;
// 	while (i < tool->philo_num)
// 	{
// 		pthread_join(tool->th[i], NULL);
// 	}
// 	pthread_mutex_destroy(tool->&mutex_philo);
// }

unsigned int	current_time(int i)
{
	unsigned int	time;
	static int	init;
	static struct timeval	start;
	struct timeval	check;

	if (init == 0)
	{
		gettimeofday(&start, NULL);
		init++;
		return (0);
	}
	gettimeofday(&check, NULL);
	if (i == 1)
		time = (check.tv_sec * 1000 + check.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000);
	if (i == 0)
		time = check.tv_usec;
	return (time);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	if (argc > 6 || argc < 5)
		return (err_msg("philo: Invalid number of argument\n", 0));
	if (info_init(&info))
		return (1);
	if (check_arg(info, argc, argv))
		return (1);
	if (parse_arg(info, argc, argv))
		return (1);
	if (argc == 6)
	{
		if (info->eat_num == 0)
			{
				end_free(info);
				return (0);
			}
	}
	info->philo = create_philo(info, info->philo);
	if (!info->philo)
		return (1);
	printf("ok\n");
	// philo(info);
	// end_free(info);
	return (0);
}
