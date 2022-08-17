/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:49:22 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/17 10:49:25 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_die(t_info *info)
{
	sem_wait(info->data);
	if (info->dead)
	{
		sem_post(info->data);
		return (1);
	}
	sem_post(info->data);
	return (0);
}

int	check_die_stop(t_philo *philo)
{
	sem_wait(philo->info->data);
	if (philo->stop || *philo->dead)
	{
		sem_post(philo->info->data);
		return (1);
	}
	sem_post(philo->info->data);
	return (0);
}

int	check_meal(t_philo *philo)
{
	if (philo->info->meal_num > 0)
	{
		if (philo->meal_count == philo->info->meal_num)
		{
			sem_wait(philo->info->data);
			philo->stop = 1;
			sem_post(philo->info->data);
			return (1);
		}
	}
	return (0);
}
