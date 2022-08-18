/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:50:33 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/17 10:50:36 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_log(t_info *info, int num, char *str)
{
	sem_wait(info->print);
	if (!check_die(info))
		printf("%llu %d %s\n", timestamp(), num, str);
	sem_post(info->print);
}

static void	is_eating(t_philo *philo)
{
	sem_wait(philo->info->fork);
	ft_log(philo->info, philo->num, "has taken a fork");
	if (philo->info->philo_num == 1)
	{
		ft_usleep(philo->info->die_time + 5);
		sem_post(philo->info->fork);
		return ;
	}
	sem_wait(philo->info->fork);
	ft_log(philo->info, philo->num, "has taken a fork");
	if (check_die_stop(philo))
	{
		sem_post(philo->info->fork);
		sem_post(philo->info->fork);
		return ;
	}
	sem_wait(philo->info->data);
	philo->last_meal = timestamp();
	sem_post(philo->info->data);
	philo->meal_count++;
	ft_log(philo->info, philo->num, "is eating");
	ft_usleep(philo->info->eat_time);
	sem_post(philo->info->fork);
	sem_post(philo->info->fork);
}

void	simulation(void *arg)
{
	t_philo	*philo;

	philo = ((t_philo *)arg);
	if (pthread_create(&philo->info->monitor_id, NULL, &monitor, (void *)philo))
		exit (err_msg(8));
	if (pthread_detach(philo->info->monitor_id))
		exit (err_msg(9));
	while (!check_die_stop(philo))
	{
		is_eating(philo);
		if (check_meal(philo) || check_die_stop(philo))
			exit (0);
		ft_log(philo->info, philo->num, "is sleeping");
		ft_usleep(philo->info->sleep_time);
		if (check_die_stop(philo))
			exit (0);
		ft_log(philo->info, philo->num, "is thinking");
		usleep(150);
	}
	exit (0);
}
