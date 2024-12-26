/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:27:25 by akharfat          #+#    #+#             */
/*   Updated: 2024/12/26 16:41:39 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_till_char(char *str, char c)
{
	int		i;
	int		len;
	char	*ret;

	(1) && (len = -1, i = -1);
	while (str[++len] && str[len] != c)
		;
	ret = g_malloc(len + 1, MALLOC);
	if (!ret)
		return (NULL);
	while (++i < len)
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}

int	ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}
