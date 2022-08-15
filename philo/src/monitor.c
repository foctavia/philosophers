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
	*tmp->dead = 1;
	ft_log(info, tmp->num, "died");
	while (!tmp->stop)
	{
		tmp->stop = 1;
		tmp = tmp->next;
	}
}

void	*monitor(void *arg)
{
	t_info	*info;

	info = ((t_info *)arg);
	info->tmp = info->philo;
	while (!info->dead && !info->tmp->stop)
	{
		// pthread_mutex_lock(&info->print);
		// printf("no. %llu, time is %llu, last meal is %llu, minus is %llu\n", info->tmp->num, info->time, info->tmp->last_meal, info->time - info->tmp->last_meal);
		// pthread_mutex_unlock(&info->print);
		if ((info->time - info->tmp->last_meal) > info->die_time && (info->time - info->tmp->last_meal) > 0)
		{
			// pthread_mutex_lock(&info->print);
			// printf("no. %llu, time is %llu, last meal is %llu, minus is %llu\n", info->tmp->num, info->time, info->tmp->last_meal, info->time - info->tmp->last_meal);
			// pthread_mutex_unlock(&info->print);
			is_dying(info, info->tmp);
			return (NULL);
		}
		info->tmp = info->tmp->next;
	}
	return (NULL);
}

// void	*waiter(void *arg)
// {
// 	t_info	*info;

// 	info = ((t_info *)arg);
// 	info->tmp = info->philo;
// 	while (!info->dead && !info->tmp->stop)
// 	{
// 		if (info->tmp->num % 2)
// 		{
// 			if (info->philo_num % 2 && info->tmp->num == info->philo_num)
// 				info->tmp->sig = 0;
// 			else
// 				info->tmp->sig = 1;
// 		}
// 		else
// 			info->tmp->sig = 0;
// 		if (timestamp(info) >= info->eat_time)
// 			info->tmp->sig++;
// 		info->tmp = info->tmp->next;
// 	}
// 	return (NULL);
// }
