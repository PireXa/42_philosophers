/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PHILOSOPHERS                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <rdas-nev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4242/42/42 42:42:42 by rdas-nev          #+#    #+#             */
/*   Updated: 4242/42/42 42:42:42 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// int array
// 0: philo number
// 1: sleeping or not
// //////////////////
// long long int array
// 0: time of last eat
// 1: time of last sleep
// //////////////////
// static int array
// 0: thread init check
// 1: eat counter

t_tt	*build_threadthings(t_tt *p, int n)
{
	p->i = malloc(sizeof(int) * 2);
	p->i[0] = n;
	p->i[1] = 0;
	p->s = (struct timeval *)malloc(sizeof(struct timeval));
	gettimeofday(p->s, NULL);
	p->li = malloc(sizeof(long long int) * 2);
	p->li[0] = gt(*p->s);
	p->li[1] = 0;
	if (p->i[0] % 2 == 0)
		usleep(5000);
	return (p);
}

void	*f_thread(void *m)
{
	static int		*si;
	t_tt			*p;
	t_philo			*a;

	si = (int [2]){0, 0};
	init_thread(m);
	a = (t_philo *)((t_m *) m)->b[si[0]];
	p = (t_tt *)((t_m *) m)->t[si[0]++];
	while (si[0] != *(((t_m *) m)->ph_n))
		;
	p = build_threadthings(p, *a->phn);
	while (*((t_m *)m)->morreu == 0 && (*a->ecnt == -1
			|| si[1] < *a->ecnt * *((t_m *)m)->ph_n) && si[0] < 1000)
	{
		if (!me_dead(*((t_m *)m)->die_t, p->li[0], *p->s))
		{
			si[1] += megacoiso(((t_m *)m), p, a);
			if (sleeper_2((t_m *)m, p, a) == 1)
				return (NULL);
		}
		else
			*((t_m *)m)->morreu = philodied(a, gt(*p->s), p->i[0], 0);
	}
	endthread(a, gt(*p->s), p->i[0], p);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_m	*m;

	if (inputcheck(ac, av) == 1)
		return (1);
	else
	{
		m = malloc(sizeof(t_m));
		masterbuilder(m, av);
		threaddoer(m, av);
		masterdestroyer(m);
		return (0);
	}
}
