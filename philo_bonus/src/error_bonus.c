/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:49:46 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/17 10:49:49 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	err_msg(int err)
{
	if (err == -1)
		ft_putstr_fd("Error: Malloc function failed\n", 2);
	else if (err == 1)
		ft_putstr_fd("Error: Invalid number of argument\n", 2);
	else if (err == 2)
		ft_putstr_fd("Error: Empty argument\n", 2);
	else if (err == 3)
		ft_putstr_fd("Error: Invalid type of argument\n", 2);
	else if (err == 4)
		ft_putstr_fd("Error: Invalid argument value\n", 2);
	else if (err == 5)
		ft_putstr_fd("Error: Invalid number of philosopher\n", 2);
	else if (err == 6)
		ft_putstr_fd("Error: Failed to open a semaphore\n", 2);
	else if (err == 7)
		ft_putstr_fd("Error: Failed to fork a process\n", 2);
	else if (err == 8)
		ft_putstr_fd("Error: Failed to create a thread\n", 2);
	else if (err == 9)
		ft_putstr_fd("Error: Failed to detach a thread\n", 2);
	return (1);
}

void	free_list(t_philo *philo)
{
	t_philo	*tmp1;
	t_philo	*tmp2;

	if (philo)
	{
		tmp1 = philo->next;
		while (tmp1 != philo)
		{
			tmp2 = tmp1;
			tmp1 = tmp1->next;
			free(tmp2);
		}
		free(tmp1);
	}
}

void	err_free(t_info *info, int err)
{
	if (info)
		free(info);
	exit (err_msg(err));
}

void	err_kill_free(t_info *info, int err)
{
	unsigned long long	i;

	i = 0;
	sem_close(info->print);
	sem_unlink("print");
	sem_close(info->data);
	sem_unlink("data");
	sem_close(info->fork);
	sem_unlink("fork");
	info->tmp = info->philo;
	while (i < info->philo_num)
	{
		kill(info->tmp->id, SIGTERM);
		info->tmp = info->tmp->next;
		i++;
	}
	if (info)
	{
		if (info->philo)
			free_list(info->philo);
		free(info);
	}
	exit (err_msg(err));
}
