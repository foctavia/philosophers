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
	if (!check_die(info) || !ft_strcmp(str, "died"))
		printf("%llu %d %s\n", timestamp(), num, str);
	pthread_mutex_unlock(&info->print);
}

static void	is_leftie(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	ft_log(philo->info, philo->num, "has taken a fork");
	if (philo->info->philo_num == 1)
	{
		usleep(philo->info->die_time * 1000);
		pthread_mutex_unlock(&philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	ft_log(philo->info, philo->num, "has taken a fork");
	if (check_die_stop(philo))
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(&philo->info->data);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->info->data);
	philo->meal_count++;
	ft_log(philo->info, philo->num, "is eating");
	usleep(philo->info->eat_time * 1000);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	is_rightie(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_log(philo->info, philo->num, "has taken a fork");
	pthread_mutex_lock(&philo->left_fork);
	ft_log(philo->info, philo->num, "has taken a fork");
	if (check_die_stop(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
		return ;
	}
	pthread_mutex_lock(&philo->info->data);
	philo->last_meal = timestamp();
	pthread_mutex_unlock(&philo->info->data);
	philo->meal_count++;
	ft_log(philo->info, philo->num, "is eating");
	usleep(philo->info->eat_time * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = ((t_philo *)arg);
	while (!check_die_stop(philo))
	{
		if (philo->num % 2)
			is_leftie(philo);
		else
			is_rightie(philo);
		if (check_meal(philo) || check_die_stop(philo))
			return (NULL);
		ft_log(philo->info, philo->num, "is sleeping");
		usleep(philo->info->sleep_time * 1000);
		if (check_die_stop(philo))
			return (NULL);
		ft_log(philo->info, philo->num, "is thinking");
		usleep(300);
	}
	return (NULL);
}
