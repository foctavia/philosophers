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

void	err_msg(char *str, int perr)
{
	if (perr == 1)
		perror(str);
	else if (perr == 2)
	{
		ft_putstr_fd(str, 2);
		free(str);
	}
	else
		ft_pustr_fd(str, 2);
	exit (1);
}

void	exit_free(t_tool *tool, char *str, int perr)
{
	if (tool)
	{
		if (tool->th)
			free(th);
		free(tool);
	}
	err_msg(str, perr);
}

void	end_free(t_tool *tool)
{
	if (tool)
	{
		if (tool->th)
			free(th);
		free(tool);
	}
}

void	tool_init(t_tool **tool)
{
	*tool = (t_tool *) malloc(sizeof(t_tool));
	if (!(*tool))
		exit_free(*tool, "malloc", 1);
	(*tool)->philo_num = 0;
	(*tool)->die_time = 0;
	(*tool)->eat_time = 0;
	(*tool)->sleep_time = 0;
	(*tool)->eat_num = 0;
	(*tool)->th = NULL;
}

void	check_parse(t_tool *tool, int argc, char **argv)
{
	tool->philo_num = ft_atoi(argc[0]);
	tool->die_time = ft_atoi(argc[1]);
	tool->eat_time = ft_atoi(argc[2]);
	tool->sleep_time = ft_atoi(argc[3]);
	if (argc == 5)
		tool->eat_num = ft_atoi(argc[4]);
}

void	*action()
{
	pthread_mutex_lock(&mutex_philo);

	pthread_mutex_unlock(&mutex_philo);
}

void	philo(t_tool *tool)
{
	int	i;

	tool->th = (pthread_t *)malloc(sizeof(pthread_t * tool->philo_num));
	if (!(tool->th))
		exit_free(tool, "malloc", 1);
	pthread_mutex_init(tool->&mutex_philo, NULL);
	i = 0;
	while (i < tool->philo_num)
	{
		pthread_create(tool->&th[i], NULL, &action, NULL);
	}
	i = 0;
	while (i < tool->philo_num)
	{
		pthread_join(tool->th[i], NULL);
	}
	pthread_mutex_destroy(tool->&mutex_philo);
}

int	main(int argc, char **argv, char **envp)
{
	t_tool	*tool;

	if (argc > 5 || argc < 4)
		err_msg("philo: Invalid number of argument\n", 0);
	tool_init(&tool);
	check_parse(tool, argc, argv);
	philo(tool);
	end_free(tool);
	return (0);
}
