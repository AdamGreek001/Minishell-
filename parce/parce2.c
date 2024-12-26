/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 01:42:19 by eel-alao          #+#    #+#             */
/*   Updated: 2024/12/26 16:40:50 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_join_char(char *s, char c)
{
	int		i;
	char	*ret;

	ret = g_malloc(ft_strlen(s) + 2, MALLOC);
	if (!ret)
		return (NULL);
	i = 0;
	while (s && s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = c;
	i++;
	ret[i] = '\0';
	return (ret);
}

int	check_qut_syntax(char *line, char qut)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] == qut)
			return (1);
		j++;
	}
	ft_putstr_fd("syntax error: unexpected end of file\n", 2);
	exit_status(1, 1);
	return (0);
}

char	*get_quoted(char *line, char c, int *i)
{
	char	*ret;

	(*i)++;
	ret = get_till_char(line + (*i), c);
	if (!ret)
		return (NULL);
	while (line[*i] && line[*i] != c)
		(*i)++;
	(*i)++;
	return (ret);
}

bool	is_token(char *line)
{
	return (!ft_strncmp(line, "<<", 2) || !ft_strncmp(line, ">>", 2)
		|| !ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
		|| !ft_strncmp(line, "|", 1));
}

char	*get_token(char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] != '>')
		return ((*i)++, ft_strdup(">"));
	else if (line[*i] == '>' && line[*i + 1] == '>')
		return (*i += 2, ft_strdup(">>"));
	else if (line[*i] == '<' && line[*i + 1] == '<')
		return (*i += 2, ft_strdup("<<"));
	else if (line[*i] == '<' && line[*i + 1] != '<')
		return ((*i)++, ft_strdup("<"));
	else
		return ((*i)++, ft_strdup("|"));
}
