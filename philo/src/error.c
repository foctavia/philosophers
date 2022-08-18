/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:59:33 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/05 14:59:35 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		ft_putstr_fd("Error: Failed to initiate mutex\n", 2);
	else if (err == 7)
		ft_putstr_fd("Error: Failed to create a thread\n", 2);
	else if (err == 8)
		ft_putstr_fd("Error: Failed to detach a thread\n", 2);
	else if (err == 9)
		ft_putstr_fd("Error: Failed to join a thread\n", 2);
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

int	err_free(t_info *info, int err)
{
	err_msg(err);
	if (info)
		free(info);
	return (1);
}

int	err_destroy_free(t_info *info, int err)
{
	err_msg(err);
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->data);
	fork_destroy(info, info->philo);
	if (info)
	{
		if (info->philo)
			free_list(info->philo);
		free(info);
	}
	return (1);
}

int	err_join_destroy_free(t_info *info, int err)
{
	err_msg(err);
	join_philo(info);
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->data);
	fork_destroy(info, info->philo);
	if (info)
	{
		if (info->philo)
			free_list(info->philo);
		free(info);
	}
	return (1);
}
