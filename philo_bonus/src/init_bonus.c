/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:49:58 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/17 10:50:01 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_info(t_info **info)
{
	*info = (t_info *) malloc(sizeof(t_info));
	if (!(*info))
		exit (err_msg(-1));
	(*info)->dead = 0;
	(*info)->philo_num = 0;
	(*info)->die_time = 0;
	(*info)->eat_time = 0;
	(*info)->sleep_time = 0;
	(*info)->meal_num = 0;
	(*info)->philo = NULL;
	(*info)->tmp = NULL;
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
			err_free(info, -1);
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

void	philo_init(t_info *info)
{
	timestamp();
	info->philo = create_philo(info, info->philo);
	info->print = sem_open("print", O_CREAT, 0644, 1);
	if (info->print == SEM_FAILED)
		err_free(info, 6);
	info->data = sem_open("data", O_CREAT, 0644, 1);
	if (info->data == SEM_FAILED)
		err_free(info, 6);
	info->fork = sem_open("fork", O_CREAT, 0644, info->philo_num);
	if (info->fork == SEM_FAILED)
		err_free(info, 6);
}
