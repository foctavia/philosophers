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

void	ft_log(t_info *info, int num, char *str)
{
	pthread_mutex_lock(&info->print);
	if (!check_die(info) || !ft_strcmp(str, "died"))
		printf("%llu %d %s\n", timestamp(), num, str);
	pthread_mutex_unlock(&info->print);
}

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
	unsigned long long	last_meal;

	info = ((t_info *)arg);
	info->tmp = info->philo;
	while (!info->dead && !info->tmp->stop)
	{
		pthread_mutex_lock(&info->data);
		last_meal = info->tmp->last_meal;
		pthread_mutex_unlock(&info->data);
		if ((timestamp() - last_meal) > info->die_time)
		{
			is_dying(info, info->tmp);
			return (NULL);
		}
		info->tmp = info->tmp->next;
	}
	return (NULL);
}
