#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

pthread_mutex_t agarra_fork, larga_fork, veoif;

typedef struct		s_forks {
	int				*fork;
	struct s_forks	*next;
} 					t_forks;

typedef struct s_philo{
	char			**args;
	int				*ind;
	t_forks 		*esq;
	t_forks 		*dir;
	pthread_mutex_t	*mt;
}					t_philo;

void printforks(t_forks *lst);

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

int	me_nao_dead(char *die_time, long long int eat_time, struct timeval start)
{
	//printf("1 = %lld 2 = %d	\n", get_time(start) - eat_time, ft_atoi(die_time));
	if (get_time(start)	 - eat_time > ft_atoi(die_time))
		return (1);
	return (0);
}

void	*fThread(void *a)
{
	int				c;
	int				sleep;
	long long int	eat_time;

	c = *(int *) ((t_philo *) a)->ind;
//	usleep(500000);
	sleep = 0;
	if (c == 4324)
		usleep(5000000);
	struct timeval start;
	gettimeofday(&start, NULL);
	eat_time = get_time(start);
	while (!me_nao_dead(((t_philo *)a)->args[2], eat_time, start))
	{
//		sleep(1);
//		printf("adress of esq: %p\n", ((t_philo *) a)->esq);
//		printf("adress of dir: %p\n", ((t_philo *) a)->dir);
		pthread_mutex_lock(&veoif);//((t_philo *) a)->mt);
		if (*((t_philo *)a)->esq->fork == 1 && *((t_philo *)a)->dir->fork == 1)
		{
			*((t_philo *)a)->esq->fork = 2;
			*((t_philo *)a)->dir->fork = 2;
			eat_time = get_time(start);
			pthread_mutex_unlock(&veoif);//((t_philo *)a)->mt);
			printf("\e[33m%lld ms | \e[0m\e[32mPhilo number: %d is eating\n\e[0m", get_time(start), c + 1);
			usleep(ft_atoi(((t_philo *) a)->args[3]) * 1000);
			printf("\e[33m%lld ms | \e[0m\e[34mPhilo number: %d is DONE eating\n\e[0m", get_time(start), c + 1);
			pthread_mutex_lock(&larga_fork);//((t_philo *) a)->mt);
			*((t_philo *)a)->esq->fork = 1;
			*((t_philo *)a)->dir->fork = 1;
			pthread_mutex_unlock(&larga_fork);//((t_philo *)a)->mt);
			sleep = 1;
		}
		else
			pthread_mutex_unlock(&veoif);//((t_philo *)a)->mt);
		if (sleep == 1)
		{
			usleep(ft_atoi(((t_philo *) a)->args[4]) * 1000);
			sleep = 0;
		}
	}
	printf("\e[31m%lld ms | \e[0m\e[31mPhilo number: %d is dead\n\e[0m", get_time(start), c + 1);
	free (((t_philo *)a)->ind);
	free(a);
	exit(0);
	return (NULL);
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

void	crono_thread(t_forks **forks)
{
	pthread_t	*t1;

	t1 = malloc(sizeof(pthread_t));
	pthread_create(t1, NULL, fThread_Timer, (void *) forks);

}

void	ft_lstfront(t_forks **lst, t_forks *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_back(t_forks **lst, t_forks *new)
{
	t_forks *tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	tmp->next = (*lst)->next;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_forks *ft_lstnew(int *content)
{
	t_forks *new;

	new = malloc(sizeof(t_forks));
	if (!new)
		return (NULL);
	new->fork = content;
	new->next = NULL;
	return (new);
}

void buildforks(t_forks **lst, int n)
{
	int i;
	int *content;

	i = 1;
	content = malloc(sizeof(int));
	*content = 1;
	*lst = NULL;
	ft_lstfront(lst, ft_lstnew(content));
	while (i < n)
	{
		content = malloc(sizeof(int));
		*content = 1;
		ft_lstadd_back(lst, ft_lstnew(content));
		i++;
	}
}

t_forks *getfork(t_forks *lst, int n)
{
	int		i;
	t_forks	*tmp;

	i = 0;
	tmp = lst;
	while (i < n)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

void printforks(t_forks *lst)
{
	t_forks *tmp;

	tmp = lst;
	while (tmp)
	{
		printf("Fork: %d ", *tmp->fork);
		printf("Address: %p |", tmp->fork);
		tmp = tmp->next;
	}
	printf("\n");
}

int main(int ac, char **av)
{
	int				i;
	t_philo 		*a;
	pthread_t		th[124535];
	t_forks 		**forks;

	if (ac != 5)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	if (ft_atoi(av[1]) == 1)
		return (0);
	forks = malloc(sizeof(t_forks *));
	buildforks(forks, ft_atoi(av[1]));
	i = 0;
	printforks(*forks);
	printf("###########################\n");
	printf("###########################\n");
	printf("###########################\n");
	pthread_mutex_init(&agarra_fork, NULL);
	pthread_mutex_init(&larga_fork, NULL);
	pthread_mutex_init(&veoif, NULL);
	//crono_thread(forks);
	while (i < ft_atoi(av[1]))
	{
		a = malloc(sizeof (t_philo));
		a->mt = malloc(sizeof(pthread_mutex_t));
//		pthread_mutex_init(a->mt, NULL);
		a->esq = NULL;
		a->dir = NULL;
		a->esq = getfork(*forks, i);
		if (i == ft_atoi(av[1]) - 1) {
			a->dir = getfork(*forks, 0);
		}
		else {
			a->dir = getfork(*forks, i + 1);
		}
//		printf("Adress: %p\n", a->esq);
//		printf("Adress: %p\n", a->dir);
//		printf("Esq: %d Dir: %d\n######################\n", *a->esq->fork, *a->dir->fork);
//		printforks(*forks);
		a->ind = malloc(sizeof (int));
		a->args = av;
		*a->ind = i;
		pthread_create(&th[i], NULL, &fThread, a);
		i++;
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_join(th[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&agarra_fork);//a->mt);
	pthread_mutex_destroy(&larga_fork);//a->mt);
	pthread_mutex_destroy(&veoif);//a->mt);
//	free(a);
	return (0);
}
