/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:27:25 by akharfat          #+#    #+#             */
/*   Updated: 2024/12/26 16:36:33 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_built(char *cmd)
{
	if (!cmd)
		return (false);
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd,
			"env") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"));
}

int	exprt_err(char *var, t_call *call)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	*call = 42;
	exit_status(1, 1);
	return (0);
}

int	unst_err(char *var)
{
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	exit_status(1, 1);
	return (0);
}

bool	check_key(char *key)
{
	int	i;

	i = -1;
	if (!key || (key[0] >= '0' && key[0] <= '9'))
		return (false);
	while (key[++i])
	{
		if (key[i] != '_' && !ft_isalnum(key[i]))
			return (false);
	}
	return (true);
}
