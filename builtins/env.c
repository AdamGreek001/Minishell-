/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 01:48:55 by eel-alao          #+#    #+#             */
/*   Updated: 2024/12/08 01:48:56 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prnt_env(int fd)
{
	t_env	*env;

	env = _env_(NULL, NULL, NULL, GET_STRCT);
	while (env)
	{
		if (!env->hidden)
		{
			ft_putstr_fd(env->key, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(env->value, fd);
			ft_putstr_fd("\n", fd);
		}
		env = env->next;
	}
	exit_status(0, 1);
}