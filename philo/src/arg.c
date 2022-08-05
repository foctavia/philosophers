/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:58:51 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/05 15:47:47 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_value(t_info *info, char *str)
{
	unsigned long long	tmp;
	char				*s;
	int					i;
	int					j;

	tmp = ft_atoi_ph(info, str);
	if (info->err)
		return ;
	s = ft_itoa_ph(info, tmp);
	i = 0;
	j = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i] && str[i] == '0' && str[i + 1] != '\0')
		i++;
	if (!info->err && ft_strcmp(&s[j], &str[i]))
		info->err = 4;
	free(s);
}

static int	validate_arg(t_info *info, int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (!info->err && argv[i][0] == '\0')
			info->err = 2;
		while (argv[i][j] && argv[i][j] == ' ')
			j++;
		if (argv[i][j] && (argv[i][j] == '+' || argv[i][j] == '-'))
			j++;
		while (argv[i][j])
		{
			if (!info->err && ft_isdigit(argv[i][j]) == 0)
				info->err = 3;
			j++;
		}
		check_value(info, argv[i]);
		i++;
	}
	if (info->err)
		return (1);
	else
		return (0);
}

static int	parse_arg(t_info *info, int argc, char **argv)
{
	info->philo_num = ft_atoi_ph(info, argv[1]);
	if (info->philo_num < 1)
	{
		info->err = 5;
		return (1);
	}
	info->die_time = ft_atoi_ph(info, argv[2]);
	info->eat_time = ft_atoi_ph(info, argv[3]);
	info->sleep_time = ft_atoi_ph(info, argv[4]);
	if (argc == 6)
		info->meal_num = ft_atoi_ph(info, argv[5]);
	return (0);
}

int	check_arg(t_info *info, int argc, char **argv)
{
	if (argc > 6 || argc < 5)
	{
		info->err = 1;
		return (1);
	}
	if (validate_arg(info, argc, argv))
		return (1);
	if (parse_arg(info, argc, argv))
		return (1);
	return (0);
}
