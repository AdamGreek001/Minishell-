/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:42:50 by akharfat          #+#    #+#             */
/*   Updated: 2024/12/24 23:15:25 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_expand(char *tkn, t_list *node, char qut)
{
	if ((qut == '\0' || qut == '\"') && ft_strchr(tkn, '$'))
	{
		if (qut == '\0')
			node->split_it = true;
		node->old = tkn;
		node->token = expand(tkn);
		if (!node->token)
			return (NULL);
	}
	else
	{
		node->old = tkn;
		node->token = tkn;
	}
	return (node->token);
}

t_list	*check_syntax(t_list *head)
{
	t_list	*tmp;

	tmp = head;
	join_nodes(head);
	if (tmp && tmp->type == PIPE)
		return (syntax_err());
	while (tmp)
	{
		if (tmp->type == HRDC && tmp->next && tmp->next->type <= 2)
		{
			if (!heredoc(tmp->next->old, tmp, tmp->next->type))
				return (NULL);
		}
		else if (tmp->type > 2 && tmp->next && (tmp->type == tmp->next->type
				|| both_reder(tmp->type, tmp->next->type)))
			return (syntax_err());
		else if (tmp->type >= 4 && tmp->next && tmp->next->type == PIPE)
			return (syntax_err());
		else if (!tmp->next && tmp->type > 2)
			return (syntax_err());
		tmp = tmp->next;
	}
	return (head);
}

t_list	*get_list_node(char *line, int *i)
{
	char	qut;
	char	*test;
	t_list	*tmp;

	if (line[*i] == '\"' || line[*i] == '\'')
	{
		if (!check_qut_syntax(line + (*i) + 1, line[*i]))
			return (NULL);
		qut = line[*i];
		test = get_quoted(line, line[*i], i);
		tmp = new_node(test, line[*i], qut);
	}
	else if (is_token(line + (*i)))
	{
		test = get_token(line, i);
		tmp = new_node(test, line[*i], '\0');
	}
	else
	{
		test = get_word(line, i);
		tmp = new_node(test, line[*i], '\0');
	}
	return (tmp);
}

t_list	*parce_line(char *line)
{
	t_list	*head;
	t_list	*tmp;
	int		i;

	(1) && (i = 0, head = NULL);
	while (line[i])
	{
		if (ft_isspace(line[i]) && ++i >= 0)
			continue ;
		tmp = get_list_node(line, &i);
		if (!tmp)
			return (NULL);
		if (!add_node_back(&head, tmp))
			return (NULL);
	}
	return (check_syntax(head));
}
