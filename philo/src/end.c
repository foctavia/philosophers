
#include "philo.h"

static void	fork_destroy(t_info *info, t_philo *philo)
{
	unsigned long long	i;
	t_philo				*tmp;

	i = 0;
	tmp = philo;
	while (i < info->philo_num)
	{
		pthread_mutex_destroy(&tmp->left_fork);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	tmp = philo;
	while (i < info->philo_num)
	{
		tmp->right_fork = NULL;
		tmp = tmp->next;
		i++;
	}
}

void	end_free(t_info *info)
{
	// unsigned long long	i;

	// i = 0;
	// while (i < info->philo_num)
	// {
	// 	pthread_join(info->tmp->id, NULL);
	// 	info->tmp = info->tmp->next;
	// 	i++;
	// }
	pthread_mutex_destroy(&info->print);
	fork_destroy(info, info->philo);
	if (info)
	{
		if (info->philo)
			free_list(info->philo);
		free(info);
	}
}