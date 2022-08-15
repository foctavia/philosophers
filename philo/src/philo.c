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

int	philo(t_info *info)
{
	unsigned long long	i;

	i = 0;
	info->tmp = info->philo;
	while (i < info->philo_num)
	{
		if (pthread_create(&info->tmp->id, NULL,
				&simulation, (void *)info->tmp) != 0)
		{
			info->err = 7;
			return (1);
		}
		info->tmp = info->tmp->next;
		i++;
	}
	if (pthread_create(&info->monitor_id, NULL, &monitor, (void *)info))
	{
		info->err = 7;
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	if (create_info(&info))
		return (1);
	if (check_arg(info, argc, argv))
		return (err_free(info, info->err));
	if (argc == 6)
	{
		if (info->meal_num == 0)
		{
			free(info);
			return (0);
		}
	}
	// printf("time to die %llu, time to eat %llu, time to sleep %llu\n", info->die_time, info->eat_time, info->sleep_time);
	if (philo_init(info))
		return (err_destroy_free(info, info->err));
	if (philo(info))
		return (err_join_destroy_free(info, info->err));
	if (join_philo(info))
		return (err_join_destroy_free(info, info->err));
	destroy_free(info);
	return (0);
}
