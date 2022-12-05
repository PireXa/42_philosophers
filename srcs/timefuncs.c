/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PHILOSOPHERS                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <fde-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4242/42/42 42:42:42 by fde-albe          #+#    #+#             */
/*   Updated: 4242/42/42 42:42:42 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long int	s_to_mil(struct timeval t)
{
	long long int	res;

	res = t.tv_sec * 1000;
	res += t.tv_usec / 1000;
	return (res);
}

long long int	gt(struct timeval start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - s_to_mil(start));
}

int	me_dead(int die_time, long long int eat_time, struct timeval start)
{
	if (gt(start) - eat_time >= die_time)
		return (1);
	return (0);
}
