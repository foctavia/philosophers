/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:59:46 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/05 14:59:53 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_info(t_info **info)
{
	*info = (t_info *) malloc(sizeof(t_info));
	if (!(*info))
		return (err_msg(-1));
	(*info)->err = 0;
	(*info)->dead = 0;
	(*info)->philo_num = 0;
	(*info)->die_time = 0;
	(*info)->eat_time = 0;
	(*info)->sleep_time = 0;
	(*info)->meal_num = 0;
	(*info)->philo = NULL;
	(*info)->tmp = NULL;
	return (0);
}

static void	add_philo(t_philo **ph1, t_philo *ph2)
{
	t_philo	*tmp;

	if (*ph1 == NULL)
	{
		*ph1 = ph2;
		return ;
	}
	tmp = *ph1;
	while (tmp->next != *ph1)
		tmp = tmp->next;
	tmp->next = ph2;
	ph2->prev = tmp;
	ph2->next = *ph1;
	(*ph1)->prev = ph2;
}

static t_philo	*create_philo(t_info *info, t_philo *philo)
{
	t_philo				*tmp;
	unsigned long long	i;

	i = 0;
	while (i < info->philo_num)
	{
		tmp = (t_philo *) malloc(sizeof(t_philo));
		if (!tmp)
		{
			info->err = -1;
			return (NULL);
		}
		tmp->num = i + 1;
		tmp->last_meal = 0;
		tmp->meal_count = 0;
		tmp->dead = &info->dead;
		tmp->stop = 0;
		tmp->next = tmp;
		tmp->prev = tmp;
		tmp->info = info;
		add_philo(&philo, tmp);
		tmp = NULL;
		i++;
	}
	return (philo);
}

static int	fork_init(t_info *info, t_philo *philo)
{
	unsigned long long	i;
	t_philo				*tmp;

	i = 0;
	tmp = philo;
	while (i < info->philo_num)
	{
		if (pthread_mutex_init(&tmp->left_fork, NULL))
		{
			info->err = 6;
			return (1);
		}
		tmp = tmp->next;
		i++;
	}
	i = 0;
	tmp = philo;
	while (i < info->philo_num)
	{
		tmp->right_fork = &tmp->prev->left_fork;
		tmp = tmp->next;
		i++;
	}
	return (0);
}

int	philo_init(t_info *info)
{
	timestamp();
	if (pthread_mutex_init(&info->print, NULL))
	{
		info->err = 6;
		return (1);
	}
	if (pthread_mutex_init(&info->data, NULL))
	{
		info->err = 6;
		return (1);
	}
	info->philo = create_philo(info, info->philo);
	if (!info->philo)
		return (1);
	if (fork_init(info, info->philo))
		return (1);
	return (0);
}
