/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:41:40 by akharfat          #+#    #+#             */
/*   Updated: 2024/12/25 20:18:19 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_opts(char **opts, int *i, t_list *s)
{
	int		j;
	char	**splt;

	j = -1;
	if (s->split_it)
	{
		splt = pool_split(s->token, SPACES);
		if (!splt)
			return (0);
		while (splt[++j])
		{
			opts[*i] = splt[j];
			(*i)++;
		}
	}
	else
	{
		opts[*i] = ft_strdup(s->token);
		if (!opts[*i])
			return (0);
		(*i)++;
	}
	return (1);
}

void	set_hrdc_fd(t_exec *node, int fd)
{
	if (node->fd_in != 0)
		close(node->fd_in);
	node->fd_in = fd;
}

char	**fill_opts(t_list **s, t_exec *new, int i)
{
	char	**opts;

	opts = g_malloc(sizeof(char *) * (i + 1), MALLOC);
	if (!opts)
		return (NULL);
	(1) && (opts[i] = NULL, i = 0);
	while (*s && (*s)->type != PIPE)
	{
		if (is_reder((*s)->type))
		{
			if ((*s)->type == HRDC)
				set_hrdc_fd(new, (*s)->hrdc_fd);
			else
				set_fd(new, (*s)->type, (*s)->next->token);
			*s = (*s)->next->next;
		}
		else
		{
			if (!set_opts(opts, &i, *s))
				return (NULL);
			*s = (*s)->next;
		}
	}
	(*s) && (*s = (*s)->next);
	return (opts);
}
