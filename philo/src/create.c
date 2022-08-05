
#include "philo.h"

int	create_info(t_info **info)
{
	*info = (t_info *) malloc(sizeof(t_info));
	if (!(*info))
		return (err_msg(-1));
	(*info)->err = 0;
	(*info)->philo_num = 0;
	(*info)->die_time = 0;
	(*info)->eat_time = 0;
	(*info)->sleep_time = 0;
	(*info)->meal_num = 0;
    (*info)->time = 0;
    (*info)->print = NULL;
	(*info)->philo = NULL;
	(*info)->tmp = NULL;
	return (0);
}

static void	add_philo(t_philo **ph1, t_philo *ph2)
{
	t_philo	*tmp;

	if (*ph1 == NULL)
	{
		*ph1 = ph2;
		return ;
	}
	tmp = *ph1;
	while (tmp->next != *ph1)
		tmp = tmp->next;
	tmp->next = ph2;
	ph2->prev = tmp;
	ph2->next = *ph1;
	(*ph1)->prev = ph2;
}

t_philo	*create_philo(t_info *info, t_philo *philo)
{
	t_philo	*tmp;
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		tmp = (t_philo *) malloc(sizeof(t_philo));
		if (!tmp)
		{
			info->err = -1;
			return (NULL);
		}
		tmp->num = i + 1;
		tmp->last_meal = 0;
        tmp->meal_count = 0;
		tmp->id = NULL;
		tmp->left_fork = NULL;
		tmp->right_fork = NULL;
		tmp->next = tmp;
		tmp->prev = tmp;
		add_philo(&philo, tmp);
		tmp = NULL;
		i++;
	}
	return (philo);
}
