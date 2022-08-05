/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:14:28 by foctavia          #+#    #+#             */
/*   Updated: 2022/07/25 15:14:38 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log(t_info *info, int num, char *str)
{
	pthread_mutex_lock(info->print);
	printf("%d Philosopher number %d %s\n", info->time, num, str);
	pthread_mutex_unlock(info->print);
}

void	is_eating(t_info *info)
{
	timestamp(info);
	pthread_mutex_lock(info->tmp->left_fork);
	log(info, info->tmp->num, "has taken a left fork")
	timestamp(info);
	pthread_mutex_lock(info->tmp->right_fork);
	log(info, info->tmp->num, "has taken a right fork");
	timestamp(info);
	log(info, info->tmp->num, "is eating");
	usleep(info->eat_time);
	timestamp(info);
	info->tmp->last_meal = info->time;
	info->meal_count++;
	pthread_mutex_unlock(info->tmp->left_fork);
	pthread_mutex_unlock(info->tmp->right_fork);
}

void	*routine(void *arg)
{
	t_info	*info;

	info = ((t_info *)arg);
	if (info->tmp->num % 2)
	{
		is_eating(info);
	}
	else
	{

	}
}

void	philo(t_info *info)
{
	int	i;
	t_philo	*tmp;

	i = 0;
	tmp = info->philo;
	while (i < info->philo_num)
	{
		info->tmp = tmp;
		pthread_create(&tmp->id, NULL, &routine, (void *)info);
		tmp = tmp->next;
		info->tmp = NULL;
		i++;
	}
	i = 0;
	while (i < info->philo_num)
	{
		pthread_join(tmp->id, NULL);
		tmp = tmp->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info	*info;

	if (create_info(&info))
		return (1);
	if (check_arg(info, argc, argv))
		return (return_free(info, info->err));
	if (argc == 6)
	{
		if (info->eat_num == 0)
			{
				end_free(info);
				return (0);
			}
	}
	if (philo_init(info))
		return (return_free(info, info->err));
	philo(info);
	printf("ok\n");
	// end_free(info);
	return (0);
}
