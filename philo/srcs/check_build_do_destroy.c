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

int	inputcheck(int ac, char **av)
{
	int	i;

	if (!(ac == 5 || ac == 6))
	{
		printf("Error: Expected 5 or 6 arguments!\n");
		return (1);
	}
	i = 0;
	while (++i < ac)
	{
		if (!ft_isnumber(av[i]))
		{
			printf("Error: Arguments must be numbers!\n");
			return (1);
		}
	}
	return (0);
}

void	masterbuilder(t_m *m, char **av)
{
	m->mt1 = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(m->mt1, NULL) != 0)
		return ;
	m->mt2 = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(m->mt2, NULL) != 0)
		return ;
	m->mt3 = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(m->mt3, NULL) != 0)
		return ;
	m->ph_n = malloc(sizeof(int));
	*m->ph_n = ft_atoi(av[1]);
	m->die_t = malloc(sizeof(int));
	*m->die_t = ft_atoi(av[2]);
	m->eat_t = malloc(sizeof(int));
	*m->eat_t = ft_atoi(av[3]);
	m->sleep_t = malloc(sizeof(int));
	*m->sleep_t = ft_atoi(av[4]);
	m->forks = malloc(sizeof(t_lst *));
	buildlst(m->forks, *m->ph_n, 1);
	m->b = malloc(sizeof(t_philo) * *m->ph_n);
	m->t = malloc(sizeof(t_tt) * *m->ph_n);
	m->morreu = malloc(sizeof(int));
	*m->morreu = 0;
}

void	philobuilder(t_m *m, int i, char **av)
{
	t_philo		*a;
	t_tt		*ta;

	a = malloc(sizeof (t_philo));
	a->e = NULL;
	a->d = NULL;
	a->e = get_item(*m->forks, i - 1, 42);
	if (i == *m->ph_n)
		a->d = get_item(*m->forks, 0, 42);
	else
		a->d = get_item(*m->forks, i, 42);
	a->phn = malloc(sizeof(int));
	*a->phn = i;
	a->ecnt = malloc(sizeof(int));
	if (av[5])
		*a->ecnt = ft_atoi(av[5]);
	else
		*a->ecnt = -1;
	a->status = malloc(sizeof(int));
	*a->status = 0;
	m->b[i - 1] = a;
	ta = malloc(sizeof(t_tt));
	m->t[i - 1] = ta;
}

void	threaddoer(t_m *m, char **av)
{
	int	i;

	i = 0;
	while (++i <= *m->ph_n)
		philobuilder(m, i, av);
	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		if (pthread_create(&m->th[i], NULL, f_thread, m) != 0)
			return ;
	}
	i = -1;
	while (++i < ft_atoi(av[1]))
		pthread_join(m->th[i], NULL);
}

void	masterdestroyer(t_m *m)
{
	pthread_mutex_destroy(m->mt1);
	pthread_mutex_destroy(m->mt2);
	pthread_mutex_destroy(m->mt3);
	free(m->mt1);
	free(m->mt2);
	free(m->mt3);
	free(m->ph_n);
	free(m->die_t);
	free(m->eat_t);
	free(m->sleep_t);
	free(m->morreu);
	deletelist(m->forks);
	free(m->b);
	free(m->t);
	free(m);
}
