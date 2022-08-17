/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:50:46 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/17 10:50:49 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned long long	timestamp(void)
{
	static int				init;
	static struct timeval	start;
	struct timeval			check;
	unsigned long long		time;

	if (init == 0)
	{
		gettimeofday(&start, NULL);
		init++;
		return (0);
	}
	gettimeofday(&check, NULL);
	time = ((check.tv_sec * 1000) + (check.tv_usec / 1000))
		- ((start.tv_sec * 1000) + (start.tv_usec / 1000));
	return (time);
}
