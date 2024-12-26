/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 01:42:19 by eel-alao          #+#    #+#             */
/*   Updated: 2024/12/26 16:40:25 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*what_to_expand(char *s, int *i)
{
	char	*ret;

	ret = ft_strdup("");
	if (!ret)
		return (NULL);
	if (s[*i] == '?')
	{
		ret = ft_strdup("?");
		if (!ret)
			return (NULL);
		(*i)++;
		return (ret);
	}
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
	{
		ret = ft_join_char(ret, s[*i]);
		if (!ret)
			return (NULL);
		(*i)++;
	}
	return (ret);
}

char	*handle_expansion(char *s, int *i, char *ret)
{
	char	*var;

	if (s[*i] == '$')
	{
		(*i)++;
		var = what_to_expand(s, i);
		if (var)
			ret = ft_strjoin(ret, _env_(NULL, var, NULL, SEARCH));
		if (!var || !ret)
			return (NULL);
	}
	else
	{
		ret = ft_join_char(ret, s[*i]);
		if (!ret)
			return (NULL);
		(*i)++;
	}
	return (ret);
}

char	*expand(char *s)
{
	char	*ret;
	int		i;

	ret = ft_strdup("");
	i = 0;
	if (!ret)
		return (NULL);
	while (ret && s[i])
	{
		if (s[i] == '$' && ((s[i + 1] >= '0' && s[i + 1] <= '9')
				|| s[i + 1] == '$'))
		{
			i += 2;
			continue ;
		}
		ret = handle_expansion(s, &i, ret);
		if (!ret)
			return (NULL);
	}
	return (ret);
}
