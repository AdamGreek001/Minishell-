/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:27:25 by akharfat          #+#    #+#             */
/*   Updated: 2024/12/26 16:37:31 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_swap(t_env *a, t_env *b)
{
	char	*key;
	char	*value;
	bool	hidden;

	key = a->key;
	value = a->value;
	hidden = a->hidden;
	a->key = b->key;
	a->value = b->value;
	a->hidden = b->hidden;
	b->key = key;
	b->value = value;
	b->hidden = hidden;
}

void	sort_export(t_env *head)
{
	t_env	*ptr1;
	t_env	*lptr;
	int		swapped;

	lptr = NULL;
	if (head == NULL)
		return ;
	while (1)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				ft_swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		if (!swapped)
			break ;
		lptr = ptr1;
	}
}

t_env	*copy_env(t_env *head)
{
	t_env	*ret;
	t_env	*tmp;

	ret = NULL;
	while (head)
	{
		tmp = copy_node(head);
		if (!tmp)
			return (NULL);
		if (!add_env(&ret, tmp->key, tmp->value, NEW))
			return (NULL);
		head = head->next;
	}
	return (ret);
}

int	disp_exprt(int fd)
{
	t_env	*tmp;

	tmp = copy_env(_env_(NULL, NULL, NULL, GET_STRCT));
	if (!tmp)
		return (0);
	sort_export(tmp);
	while (tmp)
	{
		if (ft_strcmp(tmp->value, "_"))
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(tmp->key, fd);
			if (tmp->value)
			{
				ft_putstr_fd("=\"", fd);
				ft_putstr_fd(tmp->value, fd);
				ft_putstr_fd("\"\n", fd);
			}
			else
				ft_putstr_fd("\n", fd);
		}
		tmp = tmp->next;
	}
	exit_status(0, 1);
	return (1);
}
