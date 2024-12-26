/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:27:25 by akharfat          #+#    #+#             */
/*   Updated: 2024/12/26 16:39:21 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exec	*new_exec(void)
{
	t_exec	*new;

	new = g_malloc(sizeof(t_exec), MALLOC);
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->opt = NULL;
	new->run_it = true;
	new->fd_in = 0;
	new->fd_out = 1;
	new->next = NULL;
	return (new);
}

void	add_back_exec(t_exec **head, t_exec *new)
{
	t_exec	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	**get_options(t_list **s, t_exec *new)
{
	t_list	*tmp;
	int		i;
	char	**opts;

	(1) && (i = 0, tmp = *s);
	while (tmp && tmp->type != PIPE)
	{
		if (is_reder(tmp->type))
			tmp = tmp->next->next;
		else
		{
			if (tmp->split_it)
				i += count_w(tmp->token, SPACES);
			else
				i++;
			tmp = tmp->next;
		}
	}
	opts = fill_opts(s, new, i);
	if (!opts)
		return (NULL);
	return (opts);
}

int	pipe_count(t_exec *h)
{
	int	i;

	i = 0;
	while (h)
	{
		i++;
		h = h->next;
	}
	return (i);
}

t_exec	*setup_exec_list(t_list *s, int *p_count)
{
	t_exec	*tmp;
	t_exec	*head;
	char	**opts;

	head = NULL;
	while (s)
	{
		tmp = new_exec();
		if (!tmp)
			return (NULL);
		opts = get_options(&s, tmp);
		if (!opts)
			return (NULL);
		tmp->cmd = opts[0];
		tmp->opt = opts;
		add_back_exec(&head, tmp);
		(*p_count)++;
	}
	return (head);
}
