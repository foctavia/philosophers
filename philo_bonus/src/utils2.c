/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 16:01:32 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/05 16:01:38 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	nbrlen(unsigned long long n)
{
	int	len;

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
