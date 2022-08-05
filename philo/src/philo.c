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

// void	*routine(void *arg)
// {
// 	t_info	*info;

// 	info = ((t_info *)arg);
// 	pthread_mutex_lock(&info->print);
// 	printf("Hi, i'm philosopher number %llu\n", info->tmp->num);
// 	printf("Bye from philosopher number %llu\n", info->tmp->num);
// 	pthread_mutex_unlock(&info->print);
// 	return (NULL);
// }

int	philo(t_info *info)
{
	unsigned long long	i;

	i = 0;
	info->tmp = info->philo;
	while (i < info->philo_num)
	{
		printf("begin while loop, philo no %llu\n", info->tmp->num);
		if (pthread_create(&info->tmp->id, NULL, &simulation, (void *)info))
		{
			info->err = 7;
			return (1);
		}
		info->tmp = info->tmp->next;
		i++;
	}
	i = 0;
	while (i < info->philo_num)
	{
		if (pthread_join(info->tmp->id, NULL))
		{
			info->err = 8;
			return (1);
		}
		info->tmp = info->tmp->next;
		i++;
	}
	return (0);
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
		if (info->meal_num == 0)
		{
			end_free(info);
			return (0);
		}
	}
	if (philo_init(info))
		return (return_free(info, info->err));
	if (philo(info))
		return (return_free(info, info->err));
	end_free(info);
	return (0);
}
