
#include "philo.h"

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

void	fork_init(t_info *info, t_philo *philo)
{
	int	i;
	t_philo *tmp;

	i = 0;
	tmp = philo;
	while (i < info->philo_num)
	{
		pthread_mutex_init(tmp->left_fork, NULL);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	tmp = philo;
	while (i < info->philo_num)
	{
		tmp->right_fork = tmp->prev->left_fork;
		tmp = tmp->next;
		i++;
	}
}

int	philo_init(t_info *info)
{
	timestamp(info);
	pthread_mutex_init(info->print, NULL);
	info->philo = create_philo(info, info->philo);
	if (!info->philo)
		return (1);
	fork_init(info, info->philo);
	return (0);
}