# include "../inc/philo.h"

void	ft_lstfront(t_lst **lst, t_lst *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst *tmp;

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

t_lst *ft_lstnew(int *content)
{
	t_lst *new;

	new = malloc(sizeof(t_lst));
	if (!new)
		return (NULL);
	new->q = content;
	new->next = NULL;
	return (new);
}
