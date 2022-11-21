#include "../inc/philo.h"

int ft_atoi(const char *str)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

long long int seconds_to_miliseconds(struct timeval t)
{
	long long int res;

	res = t.tv_sec * 1000;
	res += t.tv_usec / 1000;
	return (res);
}

long long int get_time(struct timeval start)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - seconds_to_miliseconds(start));
}

int	me_dead(char *die_time, long long int eat_time, struct timeval start)
{
	if (get_time(start)	 - eat_time >= ft_atoi(die_time))
		return (1);
	return (0);
}

void *fThread_Timer(void *forks)
{
	struct timeval *t1;
	struct timeval *starttime;
	long long int time;

	(void)forks;
	t1 = malloc(sizeof(struct timeval));
	starttime = malloc(sizeof(struct timeval));
	gettimeofday(starttime, NULL);
	printf("Timer started %ld\n", starttime->tv_usec / 1000);
	long long int start = starttime->tv_sec * 1000 + (starttime->tv_usec / 1000);
	while (1)
	{
		usleep(100000);
		gettimeofday(t1, NULL);
		time = t1->tv_sec * 1000 + (t1->tv_usec / 1000);
		printf("Time: %lld\n", time - start);
//		printforks(*(t_forks **)forks);
//		printf("###########################\n");
	}
	free(t1);
}

void	*fThread(void *m)
{
	int c;
	int sleeping;
	long long int eat_time;
	long long int sleep_time;
	struct timeval start;
	t_philo *a;
	static int k;
	static int deathchecker;
	static int eatchecker;
	int eattimes;

	k = 0;
	pthread_mutex_lock(((t_master *) m)->mt3);
	a = (t_philo *) ((t_master *) m)->b[k];
	usleep(500 * 1000);
	k++;
	pthread_mutex_unlock(((t_master *) m)->mt3);
	while (k != ft_atoi(a->args[1]))
		;
	c = *a->phn;
	sleeping = 0;
	gettimeofday(&start, NULL);
	eat_time = get_time(start);
	deathchecker = 0;
	eatchecker = 0;
	if (a->args[5])
		eattimes = ft_atoi(a->args[5]);
	else
		eattimes = -1;
	while (deathchecker != 1 && (eattimes == -1 || eatchecker < eattimes * k))
	{
		if (!me_dead(((t_philo *) a)->args[2], eat_time, start))
		{
			pthread_mutex_lock(((t_master *) m)->mt1);
			if (*a->esq->q == 1 && *a->dir->q == 1 && ft_atoi(a->args[1]) != 1)
			{
				*a->esq->q = 2;
				printf(PURPLE"%lld ms "YELLOW"%d has taken a fork\n"RESET, get_time(start), c);
				*a->dir->q = 2;
				printf(PURPLE"%lld ms "YELLOW"%d has taken a fork\n"RESET, get_time(start), c);
				eat_time = get_time(start);
				pthread_mutex_unlock(((t_master *) m)->mt1);
				printf(PURPLE"%lld ms "GREEN"%d is eating\n"RESET, get_time(start), c);
				usleep(ft_atoi(a->args[3]) * 1000);
				if (eattimes != -1)
					eatchecker++;
				pthread_mutex_lock(((t_master *) m)->mt2);
				*a->esq->q = 1;
				*a->dir->q = 1;
				pthread_mutex_unlock(((t_master *) m)->mt2);
				sleeping = 1;
			}
			else if (*a->esq->q == 1 && *a->dir->q == 1 && ft_atoi(a->args[1]) == 1)
			{
				*a->esq->q = 2;
				printf(PURPLE"%lld ms "YELLOW"%d has taken a fork\n"RESET, get_time(start), c);
				pthread_mutex_unlock(((t_master *) m)->mt1);
			}
			else
				pthread_mutex_unlock(((t_master *) m)->mt1);
			if (sleeping == 1 && deathchecker != 1)
			{
				printf(PURPLE"%lld ms "CYAN"%d is sleeping\n"RESET, get_time(start), c);
				sleep_time = get_time(start);
				while (get_time(start) - sleep_time <= ft_atoi(a->args[3]))
				{
					if (me_dead(((t_philo *) a)->args[2], eat_time, start))
					{
						printf(PURPLE"%lld ms "RED"%d died\n"RESET, get_time(start), c);
						*a->status = 1;
						deathchecker = 1;
						free(a->status);
						free(a->phn);
						free(a);
						return (NULL);
					}

				}
				printf(PURPLE"%lld ms "BLUE"%d is thinking\n"RESET, get_time(start), c);
				sleeping = 0;
			}
		}
		else
		{
			*a->status = 1;
			deathchecker = 1;
		}
	}
	if (*a->status == 1) {
		printf(PURPLE"%lld ms "RED"%d died\n"RESET, get_time(start), c);
	}
	free(a->status);
	free(a->phn);
	free(a);
	return (NULL);
}

int main(int ac, char **av)
{
	int				i;
	t_philo 		*a;
	t_master 		*m;

	if (!(ac == 5 || ac == 6))
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	m = malloc(sizeof(t_master));
	m->forks = malloc(sizeof(t_lst *));
	buildlst(m->forks, ft_atoi(av[1]), 1);
	m->mt1 = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(m->mt1, NULL);
	m->mt2 = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(m->mt2, NULL);
	m->mt3 = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(m->mt3, NULL);
	m->b = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	i = 1;
	while (i <= ft_atoi(av[1]))
	{
		a = malloc(sizeof (t_philo));
		a->esq = NULL;
		a->dir = NULL;
		a->esq = get_item(*m->forks, i - 1, 42);
		if (i == ft_atoi(av[1]))
			a->dir = get_item(*m->forks, 0, 42);
		else
			a->dir = get_item(*m->forks, i, 42);
		a->phn = malloc(sizeof(int));
		*a->phn = i;
		a->args = av;
		a->status = malloc(sizeof(int));
		*a->status = 0;
		m->b[i - 1] = a;
		i++;
	}
	i = -1;
	while (++i < ft_atoi(av[1]))
		pthread_create(&m->th[i], NULL, fThread, m);
	i = -1;
	while (++i < ft_atoi(av[1]))
		pthread_join(m->th[i], NULL);
	pthread_mutex_destroy(m->mt1);
	pthread_mutex_destroy(m->mt2);
	pthread_mutex_destroy(m->mt3);
	free(m->mt1);
	free(m->mt2);
	free(m->mt3);
	free(m->b);
	deletlist(m->forks);
	free(m);
	return (0);
}
