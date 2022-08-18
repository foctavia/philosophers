/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:49:14 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/17 10:49:16 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	check_value(t_info *info, char *str)
{
	unsigned long long	tmp;
	char				*s;
	int					i;
	int					j;

	tmp = ft_atoi_ph(info, str);
	s = ft_itoa_ph(info, tmp);
	i = 0;
	j = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i] && str[i] == '0' && str[i + 1] != '\0')
		i++;
	if (ft_strcmp(&s[j], &str[i]))
	{
		free(s);
		err_free(info, 4);
	}
	free(s);
}

static void	validate_arg(t_info *info, int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][0] == '\0')
			err_free(info, 2);
		while (argv[i][j] && argv[i][j] == ' ')
			j++;
		if (argv[i][j] && (argv[i][j] == '+' || argv[i][j] == '-'))
			j++;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				err_free(info, 3);
			j++;
		}
		check_value(info, argv[i]);
		i++;
	}
}

static void	parse_arg(t_info *info, int argc, char **argv)
{
	info->philo_num = ft_atoi_ph(info, argv[1]);
	if (info->philo_num < 1)
		err_free(info, 5);
	info->die_time = ft_atoi_ph(info, argv[2]);
	info->eat_time = ft_atoi_ph(info, argv[3]);
	info->sleep_time = ft_atoi_ph(info, argv[4]);
	if (argc == 6)
		info->meal_num = ft_atoi_ph(info, argv[5]);
}

void	check_arg(t_info *info, int argc, char **argv)
{
	if (argc > 6 || argc < 5)
		err_free(info, 1);
	validate_arg(info, argc, argv);
	parse_arg(info, argc, argv);
}
