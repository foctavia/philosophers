/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:35:33 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/05 18:35:38 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_log(t_info *info, int num, char *str)
{
	pthread_mutex_lock(&info->print);
	printf("%llu Philosopher number %d %s\n", info->time, num, str);
	pthread_mutex_unlock(&info->print);
}

void	is_eating(t_info *info)
{
	timestamp(info);
	pthread_mutex_lock(&info->tmp->left_fork);
	ft_log(info, info->tmp->num, "has taken a left fork");
	timestamp(info);
	pthread_mutex_lock(&info->tmp->right_fork);
	ft_log(info, info->tmp->num, "has taken a right fork");
	timestamp(info);
	ft_log(info, info->tmp->num, "is eating");
	usleep(info->eat_time * 1000);
	timestamp(info);
	info->tmp->last_meal = info->time;
	info->tmp->meal_count++;
	pthread_mutex_unlock(&info->tmp->left_fork);
	pthread_mutex_unlock(&info->tmp->right_fork);
}

void	*simulation(void *arg)
{
	t_info	*info;

	info = ((t_info *)arg);
	if (info->tmp->num % 2)
	{
		is_eating(info);
	}
	else
	{
		printf("even num\n");
	}
	return (NULL);
}
