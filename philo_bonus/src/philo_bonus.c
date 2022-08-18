/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:50:15 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/17 10:50:18 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo(t_info *info)
{
	unsigned long long	i;
	t_philo				*tmp;

	i = 0;
	tmp = info->philo;
	while (i < info->philo_num)
	{
		tmp->id = fork();
		if (tmp->id < 0)
			exit (err_msg(7));
		if (tmp->id == 0)
			simulation(tmp);
		tmp = tmp->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info	*info;

	create_info(&info);
	sem_unlink("print");
	sem_unlink("data");
	sem_unlink("fork");
	check_arg(info, argc, argv);
	if (argc == 6)
	{
		if (info->meal_num == 0)
		{
			free(info);
			return (0);
		}
	}
	philo_init(info);
	philo(info);
	terminate(info);
	unlink_free(info);
	return (0);
}
