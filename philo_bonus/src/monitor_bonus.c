/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:50:07 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/17 10:50:10 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	is_dying(t_info *info, t_philo *tmp)
{
	ft_log(info, tmp->num, "died");
	sem_wait(info->data);
	*tmp->dead = 1;
	exit (1);
	sem_post(info->data);
}

void	*monitor(void *arg)
{
	t_philo				*philo;
	unsigned long long	last_meal;

	philo = ((t_philo *)arg);
	while (!check_die_stop(philo))
	{
		usleep(200);
		sem_wait(philo->info->data);
		last_meal = philo->last_meal;
		sem_post(philo->info->data);
		if ((timestamp() - last_meal) > philo->info->die_time)
		{
			is_dying(philo->info, philo);
			return (NULL);
		}
	}
	return (NULL);
}
