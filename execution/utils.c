/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 02:05:43 by eel-alao          #+#    #+#             */
/*   Updated: 2024/12/15 12:06:19 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_reder(int type)
{
	return (type >= 4);
}

char	**get_char_env(char **envv, int set)
{
	static char	**env;

	if (set)
		env = envv;
	return (env);
}
