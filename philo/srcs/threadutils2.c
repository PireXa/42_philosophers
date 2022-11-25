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

int	sleeper(t_m *m, t_tt *t, t_philo *a, int *s)
{
	printf(P"%lld ms "C"%d is sleeping\n", gt(*t->s), t->i[0]);
	while (gt(*t->s) - t->li[1] <= *m->sleep_t && *s == 0)
	{
		if (me_dead(*m->die_t, t->li[0], *t->s))
		{
			philodied(a, gt(*t->s), t->i[0], 1);
			free(t->i);
			free(t->s);
			free(t->li);
			free(t);
			return (1);
		}
	}
	printf(P"%lld ms "B"%d is thinking\n", gt(*t->s), t->i[0]);
	return (0);
}

void	unllock(t_philo *a, t_m *m, t_tt *p)
{
	forkaction(a, gt(*p->s), p->i[0]);
	pthread_mutex_unlock(((t_m *)m)->mt1);
}

int	eater(t_m *m, t_tt *p, t_philo *a)
{
	p->li[0] = gt(*p->s);
	return (eat(a, ((t_m *)m), p, p->i));
}

int	sleeper_2(t_m *m, t_tt *p, t_philo *a)
{
	if (p->i[1] == 1 && *((t_m *)m)->morreu != 1)
	{
		p->li[1] = gt(*p->s);
		if (sleeper((t_m *)m, p, a, ((t_m *)m)->morreu) == 1)
		{
			*((t_m *)m)->morreu = 1;
			return (1);
		}
		p->i[1] = 0;
	}
	return (0);
}

int	megacoiso(t_m *m, t_tt *p, t_philo *a)
{
	pthread_mutex_lock(((t_m *) m)->mt1);
	if (*a->e->q == 1 && *a->d->q == 1 && *((t_m *) m)->ph_n != 1)
		return (eater(((t_m *) m), p, a));
	else if (*a->e->q == 1 && *a->d->q == 1 && *((t_m *) m)->ph_n == 1)
	{
		unllock(a, ((t_m *) m), p);
		return (0);
	}
	else
		pthread_mutex_unlock(((t_m *) m)->mt1);
	return (0);
}
