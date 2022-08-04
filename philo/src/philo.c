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

// void	*routine()
// {
// 	pthread_mutex_lock(&mutex_philo);

// 	pthread_mutex_unlock(&mutex_philo);
// }

// void	philo(t_tool *tool)
// {
// 	int	i;

// 	tool->th = (pthread_t *)malloc(sizeof(pthread_t * tool->philo_num));
// 	if (!(tool->th))
// 		exit_free(tool, "malloc", 1);
// 	pthread_mutex_init(tool->&mutex_philo, NULL);
// 	i = 0;
// 	while (i < tool->philo_num)
// 	{
// 		pthread_create(tool->&th[i], NULL, &routine, NULL);
// 	}
// 	i = 0;
// 	while (i < tool->philo_num)
// 	{
// 		pthread_join(tool->th[i], NULL);
// 	}
// 	pthread_mutex_destroy(tool->&mutex_philo);
// }

void	timestamp(t_info *info)
{
	static int	init;
	static struct timeval	start;
	struct timeval	check;

	if (init == 0)
	{
		gettimeofday(&start, NULL);
		init++;
		return ;
	}
	gettimeofday(&check, NULL);
	info->time = (check.tv_sec * 1000 + check.tv_usec / 1000)
			- (start.tv_sec * 1000 + start.tv_usec / 1000);
}

int	philo_init(t_info *info)
{
	timestamp(info);
	pthread_mutex_init(&info->print, NULL);
	info->fork = create_fork(info, info->fork);
	info->philo = create_philo(info, info->philo);
	if (!info->fork || !info->philo)
		return (return_free(info, info->free));
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
		if (info->eat_num == 0)
			{
				end_free(info);
				return (0);
			}
	}
	philo_init(info);
	printf("ok\n");
	// philo(info);
	// end_free(info);
	return (0);
}
