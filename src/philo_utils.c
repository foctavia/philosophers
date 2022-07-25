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

long long	ft_atoi(t_tool *tool, const char *str)
{
	int			i;
	int			neg;
	long long	nbr;

	i = 0;
	neg = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	nbr = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nbr = ((nbr * 10) + (str[i] - '0'));
		i++;
	}
	if (((str[0] != '0' || str[1] != '\0') && nbr == 0) || neg < 0)
		exit_free(tool, ft_strjoin(tool, str, ": Invalid type of arguments\n"), 2);
	return (nbr);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strjoin(t_tool *tool, char const *s1, char const *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new)
		exit_free(tool, "malloc", 1);
	i = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}