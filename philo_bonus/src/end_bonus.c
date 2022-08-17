/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:49:31 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/17 10:49:34 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlink_free(t_info *info)
{
	sem_close(info->print);
	sem_unlink("print");
	sem_close(info->data);
	sem_unlink("data");
	sem_close(info->fork);
	sem_unlink("fork");
	if (info)
	{
		if (info->philo)
			free_list(info->philo);
		free(info);
	}
}

void	terminate(t_info *info)
{
	unsigned long long	i;
	int					exit_status;

	i = 0;
	info->tmp = info->philo;
	waitpid(-1, &exit_status, 0);
	if (WEXITSTATUS(exit_status) == 1)
	{
		while (i < info->philo_num)
		{
			kill(info->tmp->id, SIGTERM);
			info->tmp = info->tmp->next;
			i++;
		}
	}
	else
	{
		while (i < info->philo_num)
		{
			waitpid(info->tmp->id, NULL, 0);
			info->tmp = info->tmp->next;
			i++;
		}
	}
}
