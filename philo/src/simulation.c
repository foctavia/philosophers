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
	if (!info->dead || !ft_strcmp(str, "died"))
	{
		printf("%llu Philosopher no. %d %s\n", timestamp(info), num, str);
	}
	pthread_mutex_unlock(&info->print);
}

static void	is_leftie(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	ft_log(philo->info, philo->num, "has taken a left fork");
	pthread_mutex_lock(philo->right_fork);
	if (philo->stop || *philo->dead)
		return ;
	ft_log(philo->info, philo->num, "has taken a right fork");
	if (philo->stop || *philo->dead)
		return ;
	philo->last_meal = timestamp(philo->info);
	// pthread_mutex_lock(&philo->info->print);
	// printf("no. %llu, last meal is %llu\n", philo->num, philo->last_meal);
	// pthread_mutex_unlock(&philo->info->print);
	philo->meal_count++;
	ft_log(philo->info, philo->num, "is eating");
	usleep(philo->info->eat_time * 1000);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	is_rightie(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_log(philo->info, philo->num, "has taken a right fork");
	pthread_mutex_lock(&philo->left_fork);
	if (philo->stop || *philo->dead)
		return ;
	ft_log(philo->info, philo->num, "has taken a left fork");
	if (philo->stop || *philo->dead)
		return ;
	philo->last_meal = timestamp(philo->info);
	philo->meal_count++;
	// pthread_mutex_lock(&philo->info->print);
	// printf("no. %llu, last meal is %llu\n", philo->num, philo->last_meal);
	// pthread_mutex_unlock(&philo->info->print);
	ft_log(philo->info, philo->num, "is eating");
	usleep(philo->info->eat_time * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

int	meal_count(t_philo *philo)
{
	if (philo->info->meal_num > 0)
	{
		if (philo->meal_count == philo->info->meal_num)
		{
			philo->stop = 1;
			return (1);
		}
	}
	return (0);
}

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = ((t_philo *)arg);
	while (!philo->stop || !(*philo->dead))
	{
		if (philo->stop || *philo->dead)
			return (NULL);
		ft_log(philo->info, philo->num, "is thinking");
		usleep(100);
		if (meal_count(philo) || philo->stop || *philo->dead)
			return (NULL);
		if (philo->info->philo_num % 2 && philo->num == philo->info->philo_num)
			is_leftie(philo);
		else if (philo->num % 2)
			is_leftie(philo);
		else
			is_rightie(philo);
		if (meal_count(philo) || philo->stop || *philo->dead)
			return (NULL);
		ft_log(philo->info, philo->num, "is sleeping");
		usleep(philo->info->sleep_time * 1000);
	}
	return (NULL);
}
