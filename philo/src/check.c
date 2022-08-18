/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:13:59 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/16 17:14:03 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die(t_info *info)
{
	pthread_mutex_lock(&info->data);
	if (info->dead)
	{
		pthread_mutex_unlock(&info->data);
		return (1);
	}
	pthread_mutex_unlock(&info->data);
	return (0);
}

int	check_die_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->data);
	if (philo->stop || *philo->dead)
	{
		pthread_mutex_unlock(&philo->info->data);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->data);
	return (0);
}

int	check_meal(t_philo *philo)
{
	if (philo->info->meal_num > 0)
	{
		if (philo->meal_count == philo->info->meal_num)
		{
			pthread_mutex_lock(&philo->info->data);
			philo->stop = 1;
			pthread_mutex_unlock(&philo->info->data);
			return (1);
		}
	}
	return (0);
}
