/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 02:05:10 by eel-alao          #+#    #+#             */
/*   Updated: 2024/12/25 19:44:38 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_value(char *var, int j, t_call *call)
{
	char	*value;

	if (!var[j])
		return (NULL);
	if (var[j] == '+' && var[j + 1] != '=')
		return (exprt_err(var, call), NULL);
	if (var[j] == '+')
	{
		*call = ADD;
		j++;
	}
	j++;
	value = ft_strdup(var + j);
	if (!value)
		return (*call = 1337, NULL);
	return (value);
}

int	export_all(char **opts)
{
	int		i;
	int		j;
	t_env	env;
	t_call	call;

	(1) && (i = 0, env.tmp = 0);
	while (opts[++i])
	{
		(1) && (j = 0, call = NEW);
		while (opts[i][j] && opts[i][j] != '=' && opts[i][j] != '+')
			j++;
		env.key = get_till_char(opts[i], opts[i][j]);
		if (!env.key)
			return (0);
		env.value = get_value(opts[i], j, &call);
		if (!env.value && call == 1337)
			return (0);
		if (!check_key(env.key) || opts[i][0] == '='
				|| !env.key[0])
			(1) && (exprt_err(opts[i], &call), env.tmp++);
		if (call != 42)
			_env_(NULL, env.key, env.value, call);
	}
	if (!env.tmp)
		exit_status(0, 1);
	return (1);
}

int	unset_all(char **opts)
{
	int	i;
	int	tmp;

	i = -1;
	tmp = 0;
	while (opts[++i])
	{
		if (!check_key(opts[i]) && ++tmp)
			unst_err(opts[i]);
		else
			_env_(NULL, opts[i], NULL, REMOVE);
	}
	if (!tmp)
		exit_status(0, 1);
	return (1);
}

int	builtin_nf(t_exec *node)
{
	if (!node->run_it)
		return (0);
	if (!ft_strcmp(node->cmd, "echo"))
		return (echo(node, node->fd_out));
	else if (!ft_strcmp(node->cmd, "exit"))
		return (my_exit(node));
	else if (!ft_strcmp(node->cmd, "env"))
		return (prnt_env(node->fd_out), 1);
	else if (!ft_strcmp(node->cmd, "export"))
	{
		if (!node->opt[1])
			return (disp_exprt(node->fd_out));
		else
			export_all(node->opt);
	}
	else if (!ft_strcmp(node->cmd, "unset"))
		return (unset_all(node->opt));
	else if (!ft_strcmp(node->cmd, "cd"))
		return (cd(node->opt[1]));
	else if (!ft_strcmp(node->cmd, "pwd"))
		return (pwd(node->fd_out));
	return (1);
}

int	builtin_f(t_exec *node)
{
	if (!ft_strcmp(node->cmd, "echo"))
		return (echo(node, 1));
	else if (!ft_strcmp(node->cmd, "exit"))
		return (my_exit(node));
	else if (!ft_strcmp(node->cmd, "env"))
		return (prnt_env(1), 1);
	else if (!ft_strcmp(node->cmd, "export"))
	{
		if (!node->opt[1])
			return (disp_exprt(1));
		else
			export_all(node->opt);
	}
	else if (!ft_strcmp(node->cmd, "unset"))
		return (unset_all(node->opt));
	else if (!ft_strcmp(node->cmd, "cd"))
		return (cd(node->opt[1]));
	else if (!ft_strcmp(node->cmd, "pwd"))
		return (pwd(1));
	return (1);
}
