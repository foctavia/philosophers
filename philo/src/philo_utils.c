/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:16:58 by foctavia          #+#    #+#             */
/*   Updated: 2022/07/25 15:30:03 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	int			i;
	unsigned long long	nbr;

	i = 0;
	nbr = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (!info->err && str[i] == '-')
			info->err = 4;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nbr = ((nbr * 10) + (str[i] - '0'));
		i++;
	}
	if (!info->err && nbr == 0 && (str[0] != '0' || str[1] != '\0'))
		info->err = 4;
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

static int	nbrlen(unsigned long long n)
{
	int			len;

	len = 1;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	putnbr(unsigned long long n, char *str, int i)
{
	if (n > 9)
		putnbr(n / 10, str, i - 1);
	str[i] = (n % 10) + 48;
}

char	*ft_itoa_ph(t_info *info, unsigned long long n)
{
	char	*str;
	int		len;

	len = nbrlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str && !info->err)
	{
		info->err = -1;
		return (NULL);
	}
	putnbr(n, str, len - 1);
	str[len] = '\0';
	return (str);
}