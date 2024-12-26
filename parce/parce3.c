/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 01:42:19 by eel-alao          #+#    #+#             */
/*   Updated: 2024/12/26 16:41:00 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_char_token(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '\'' || c == '\"');
}

char	*get_word(char *line, int *i)
{
	char	*ret;
	int		len;

	ret = NULL;
	len = ft_strlen(line);
	while (*i < len && !ft_isspace(line[*i]) && !is_char_token(line[*i]))
	{
		ret = ft_join_char(ret, line[*i]);
		if (!ret)
			return (NULL);
		(*i)++;
	}
	return (ret);
}

t_token	get_type(char *token)
{
	if (!ft_strcmp(token, "|"))
		return (PIPE);
	else if (!ft_strcmp(token, ">"))
		return (R_OUT);
	else if (!ft_strcmp(token, ">>"))
		return (APND);
	else if (!ft_strcmp(token, "<<"))
		return (HRDC);
	else if (!ft_strcmp(token, "<"))
		return (R_IN);
	return (WORD);
}

int	add_node_back(t_list **head, t_list *new)
{
	t_list	*tmp;

	if (!new)
		return (0);
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

t_list	*new_node(char *tkn, char char_after, char qut)
{
	static t_list	*prev;
	t_list			*node;

	if (qut == '\r' && !tkn && char_after == '\n')
		return (prev = NULL, NULL);
	if (!tkn)
		return (NULL);
	node = g_malloc(sizeof(t_list), MALLOC);
	if (!node)
		return (NULL);
	node->split_it = false;
	node->token = check_expand(tkn, node, qut);
	if (!node->token)
		return (NULL);
	node->spc_after = false;
	node->spc_before = false;
	(ft_isspace(char_after)) && (node->spc_after = true);
	(prev && prev->spc_after) && (node->spc_before = true);
	(qut == '\'') && (node->type = SGL_Q);
	(qut == '\"') && (node->type = DBL_Q);
	(qut == '\0') && (node->type = get_type(tkn));
	node->next = NULL;
	node->prev = prev;
	prev = node;
	return (node);
}
