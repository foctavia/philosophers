
#include "philo.h"

int err_msg(int err)
{
    if (err == -1)
        ft_putstr_fd("Error: Insufficient memory\n", 2);
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
    return (1);
}

static void free_list(t_philo *philo)
{
    t_philo *tmp1;
    t_philo *tmp2;

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

int	return_free(t_info *info, int err)
{
    err_msg(err);
	if (info)
	{
		if (info->fork)
			free(info->fork);
        if (info->print)
            free(info->print);
		if (info->philo)
			free_list(info->philo);
		free(info);
	}
	return (1);
}

void	end_free(t_info *info)
{
	if (info)
	{
		if (info->fork)
			free(info->fork);
        if (info->print)
            free(info->print);
		if (info->philo)
			free_list(info->philo);
		free(info);
	}
}