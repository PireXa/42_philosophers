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

t_lst	*get_item(t_lst *lst, int index, int flag)
{
	int		i;
	t_lst	*tmp;

	if (flag == 0)
		return (NULL);
	i = 0;
	tmp = lst;
	while (i < index)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

void	buildlst(t_lst **lst, int size, int cnt)
{
	int	i;
	int	*content;

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

void	deletelist(t_lst **lst)
{
	t_lst	*tmp;

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

int	ft_atoi(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

int	ft_isnumber(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
