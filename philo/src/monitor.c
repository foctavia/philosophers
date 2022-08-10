
#include "philo.h"

static void	is_dying(t_info *info, t_philo *tmp)
{
	tmp->dead = 1;
	ft_log(info, tmp->num, "died");
	while (!tmp->stop)
	{
		tmp->stop = 1;
		tmp = tmp->next;
	}
}

void	*monitor(void *arg)
{
	t_info	*info;

	info = ((t_info *)arg);
	info->tmp = info->philo;
	while (!info->tmp->dead)
	{
		if (timestamp(info) - info->tmp->last_meal > info->die_time)
		{
			is_dying(info, info->tmp);
			return (NULL);
		}
		info->tmp = info->tmp->next;
	}
	return (NULL);
}