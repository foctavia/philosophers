/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:51:07 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/17 10:51:11 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	if (!str)
		err_free(info, -1);
	putnbr(n, str, len - 1);
	str[len] = '\0';
	return (str);
}
