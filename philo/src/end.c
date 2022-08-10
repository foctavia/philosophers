/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:11:19 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/10 17:11:22 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_destroy(t_info *info, t_philo *philo)
{
	unsigned long long	i;
	t_philo				*tmp;

	i = 0;
	tmp = philo;
	while (i < info->philo_num)
	{
		pthread_mutex_destroy(&tmp->left_fork);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	tmp = philo;
	while (i < info->philo_num)
	{
		tmp->right_fork = NULL;
		tmp = tmp->next;
		i++;
	}
}

void	destroy_free(t_info *info)
{
	pthread_mutex_destroy(&info->print);
	fork_destroy(info, info->philo);
	if (info)
	{
		if (info->philo)
			free_list(info->philo);
		free(info);
	}
}

static void	unlock_fork(t_info *info)
{
	unsigned long long	i;

	i = 0;
	info->tmp = info->philo;
	if (info->philo_num == 1)
		pthread_mutex_unlock(&info->philo->left_fork);
	while (i < info->philo_num)
	{
		pthread_mutex_unlock(&info->tmp->left_fork);
		info->tmp = info->tmp->next;
		i++;
	}
}

int	join_philo(t_info *info)
{
	unsigned long long	i;

	i = 0;
	info->tmp = info->philo;
	if (pthread_join(info->monitor_id, NULL))
	{
		info->err = 8;
		return (1);
	}
	unlock_fork(info);
	while (i < info->philo_num)
	{
		if (pthread_join(info->tmp->id, NULL))
		{
			info->err = 8;
			return (1);
		}
		info->tmp = info->tmp->next;
		i++;
	}
	pthread_mutex_unlock(&info->print);
	return (0);
}
