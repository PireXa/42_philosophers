#include "../inc/philo.h"

void printlst(t_lst *lst)
{
	t_lst *tmp;

	tmp = lst;
	while (tmp)
	{
		printf("Item: %d ", *tmp->q);
		tmp = tmp->next;
	}
	printf("\n");
}

t_lst *get_item(t_lst *lst, int index, int flag)
{
	int		i;
	t_lst	*tmp;

	if (flag == 0)
		return	NULL;
	i = 0;
	tmp = lst;
	while (i < index)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

void buildlst(t_lst **lst, int size, int cnt)
{
	int i;
	int *content;

	i = 1;
	content = malloc(sizeof(int));
	*content = cnt;
	*lst = NULL;
	ft_lstfront(lst, ft_lstnew(content));
	while (i < size)
	{
		content = malloc(sizeof(int));
		*content = cnt;
		ft_lstadd_back(lst, ft_lstnew(content));
		i++;
	}
}

void	crono_thread(t_lst **forks)
{
	pthread_t	*t1;

	t1 = malloc(sizeof(pthread_t));
	pthread_create(t1, NULL, fThread_Timer, (void *) forks);
}

void deletlist(t_lst **lst)
{
	t_lst *tmp;

	tmp = *lst;
	while (tmp)
	{
		*lst = (*lst)->next;
		free(tmp->q);
		free(tmp);
		tmp = *lst;
	}
	free(lst);
}

//int eatcounter(char **args, )