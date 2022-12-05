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

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

// philo is thinking
# define B "\033[0;34m"
// philo died
# define R "\033[1;31m"
// philo is eating
# define G "\033[0;32m"
// philo has taken a fork
# define Y "\033[0;33m"
// philo is sleeping
# define C "\033[0;36m"
// timestamp
# define P "\033[0;35m"
# define RE "\033[0m"

typedef struct s_lst
{
	int				*q;
	struct s_lst	*next;
}					t_lst;

typedef struct s_philo
{
	t_lst		*e;
	t_lst		*d;
	int			*phn;
	int			*status;
	int			*ecnt;
}					t_philo;

typedef struct threadthings
{
	long long int	*li;
	int				*i;
	struct timeval	*s;
}					t_tt;

typedef struct s_master
{
	pthread_mutex_t	*mt1;
	pthread_mutex_t	*mt2;
	pthread_mutex_t	*mt3;
	int				*ph_n;
	int				*die_t;
	int				*eat_t;
	int				*sleep_t;
	t_lst			**forks;
	t_philo			**b;
	pthread_t		th[124535];
	t_tt			**t;
	int				*morreu;
}						t_m;

void			*f_thread(void *m);
t_lst			*get_item(t_lst *lst, int index, int flag);
void			buildlst(t_lst **lst, int n, int cnt);
t_lst			*ft_lstnew(int *content);
void			ft_lstadd_back(t_lst **lst, t_lst *new);
void			ft_lstfront(t_lst **lst, t_lst *new);
void			deletelist(t_lst **lst);
int				ft_atoi(const char *str);
long long int	gt(struct timeval start);
int				me_dead(int dtime, long long int etime, struct timeval s);
int				ft_isnumber(const char *str);
int				inputcheck(int ac, char **av);
void			masterbuilder(t_m *m, char **av);
void			threaddoer(t_m *m, char **av);
void			masterdestroyer(t_m *m);
void			forkaction(t_philo *a, long long int t, int i);
void			endthread(t_philo *a, long long int t, int i, t_tt *ta);
int				philodied(t_philo *a, long long int t, int i, int flag);
int				eat(t_philo *a, t_m *m, t_tt *p, int *i);
void			init_thread(t_m *m);
int				sleeper(t_m *m, t_tt *t, t_philo *a, int *s);
int				sleeper_2(t_m *m, t_tt *p, t_philo *a);
void			unllock(t_philo *a, t_m *m, t_tt *p);
int				eater(t_m *m, t_tt *p, t_philo *a);
int				megacoiso(t_m *m, t_tt *p, t_philo *a);

#endif
