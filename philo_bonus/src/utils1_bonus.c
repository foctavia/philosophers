/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:50:59 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/17 10:51:02 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0)
		return ;
	while (*s)
		write (fd, s++, 1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	else
		return (0);
}

unsigned long long	ft_atoi_ph(t_info *info, const char *str)
{
	int					i;
	unsigned long long	nbr;

	i = 0;
	nbr = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			err_free(info, 4);
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nbr = ((nbr * 10) + (str[i] - '0'));
		i++;
	}
	if (nbr == 0 && (str[0] != '0' || str[1] != '\0'))
		err_free(info, 4);
	return (nbr);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
