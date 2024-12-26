/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 01:42:19 by eel-alao          #+#    #+#             */
/*   Updated: 2024/12/26 16:41:04 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	both_reder(t_token t1, t_token t2)
{
	return (t1 >= 4 && t2 >= 4);
}

t_list	*syntax_err(void)
{
	ft_putstr_fd("Syntax error\n", 2);
	return (NULL);
}

char	*get_old(char *cur, char *next, t_token next_type)
{
	if (!ft_strcmp(cur, "$") && next_type > 0)
		return (ft_strdup(next));
	else if (!ft_strcmp(next, "$") && next_type == 0)
		return (ft_strdup(cur));
	else
		return (ft_strjoin(cur, next));
}

int	join_nodes(t_list *head)
{
	t_list	*cur;
	t_list	*tmp;

	cur = head;
	while (cur)
	{
		tmp = cur->next;
		while (tmp && !tmp->spc_before && tmp->type <= 2 && cur->type <= 2)
		{
			if (tmp != cur)
			{
				cur->token = ft_strjoin(cur->token, tmp->token);
				cur->old = get_old(cur->old, tmp->old, tmp->type);
			}
			if (cur != tmp && (!cur->token || !cur->old))
				return (0);
			(tmp->type != 0) && (cur->type = tmp->type);
			(tmp->split_it) && (cur->split_it = true);
			cur->next = tmp->next;
			tmp = tmp->next;
		}
		cur = cur->next;
	}
	return (1);
}
