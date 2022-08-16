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
	pthread_mutex_destroy(&info->data);
	fork_destroy(info, info->philo);
	if (info)
	{
		if (info->philo)
			free_list(info->philo);
		free(info);
	}
}

int	join_philo(t_info *info)
{
	unsigned long long	i;

	i = 0;
	if (pthread_join(info->monitor_id, NULL))
	{
		info->err = 8;
		return (1);
	}
	info->tmp = info->philo;
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
	return (0);
}
