/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:27:25 by akharfat          #+#    #+#             */
/*   Updated: 2024/12/26 16:39:55 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_w(char const *s, char *del)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] && ft_strchr(del, s[i]) != NULL)
			i++;
		if (s[i] != '\0')
			cnt++;
		while (s[i] && ft_strchr(del, s[i]) == NULL)
			i++;
	}
	return (cnt);
}

static char	*ft_strndup(const char *s1, int n)
{
	int		i;
	char	*new;

	i = 0;
	new = (char *)g_malloc(n + 1, MALLOC);
	if (!new)
		return (NULL);
	while (i < n)
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**pool_split(char const *s, char *del)
{
	int		i;
	int		index;
	int		wc;
	char	**arr;

	if (!s)
		return (NULL);
	(1) && (wc = count_w(s, del), index = -1);
	arr = g_malloc((sizeof(char *)) * (wc + 1), MALLOC);
	if (!arr)
		return (NULL);
	while (++index < wc)
	{
		i = 0;
		while (*s && ft_strchr(del, *s) != NULL)
			s++;
		while (*(s + i) && ft_strchr(del, *(s + i)) == NULL)
			i++;
		arr[index] = ft_strndup(s, i);
		if (arr[index] == NULL)
			return (NULL);
		while (*s && ft_strchr(del, *s) == NULL)
			s++;
	}
	return (arr[index] = NULL, arr);
}
