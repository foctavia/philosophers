/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:18:21 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/10 16:18:24 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	is_dying(t_info *info, t_philo *tmp)
{
	pthread_mutex_lock(&info->data);
	*tmp->dead = 1;
	pthread_mutex_unlock(&info->data);
	ft_log(info, tmp->num, "died");
	pthread_mutex_lock(&info->data);
	while (!tmp->stop)
	{
		tmp->stop = 1;
		tmp = tmp->next;
	}
	pthread_mutex_unlock(&info->data);
}

void	*monitor(void *arg)
{
	t_info				*info;
	t_philo				*tmp;
	unsigned long long	last_meal;

	info = ((t_info *)arg);
	tmp = info->philo;
	while (!check_die_stop(tmp))
	{
		pthread_mutex_lock(&info->data);
		last_meal = tmp->last_meal;
		pthread_mutex_unlock(&info->data);
		if ((timestamp() - last_meal) > info->die_time)
		{
			is_dying(info, tmp);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	create_monitor(t_info *info)
{
	if (pthread_create(&info->monitor_id, NULL, &monitor, (void *)info))
	{
		info->err = 7;
		return (1);
	}
	if (pthread_detach(info->monitor_id))
	{
		info->err = 8;
		return (1);
	}
	return (0);
}
