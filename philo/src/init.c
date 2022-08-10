/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:59:46 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/05 14:59:53 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	timestamp(t_info *info)
{
	static int				init;
	static struct timeval	start;
	struct timeval			check;

	if (init == 0)
	{
		gettimeofday(&start, NULL);
		init++;
		return (0);
	}
	gettimeofday(&check, NULL);
	info->time = ((check.tv_sec * 1000) + (check.tv_usec / 1000))
		- ((start.tv_sec * 1000) + (start.tv_usec / 1000));
	return (info->time);
}

static int	fork_init(t_info *info, t_philo *philo)
{
	unsigned long long	i;
	t_philo				*tmp;

	i = 0;
	tmp = philo;
	while (i < info->philo_num)
	{
		if (pthread_mutex_init(&tmp->left_fork, NULL))
		{
			info->err = 6;
			return (1);
		}
		tmp = tmp->next;
		i++;
	}
	i = 0;
	tmp = philo;
	while (i < info->philo_num)
	{
		tmp->right_fork = &tmp->prev->left_fork;
		tmp = tmp->next;
		i++;
	}
	return (0);
}

int	philo_init(t_info *info)
{
	timestamp(info);
	if (pthread_mutex_init(&info->print, NULL))
	{
		info->err = 6;
		return (1);
	}
	info->philo = create_philo(info, info->philo);
	if (!info->philo)
		return (1);
	if (fork_init(info, info->philo))
		return (1);
	return (0);
}
