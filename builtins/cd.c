/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 02:05:13 by eel-alao          #+#    #+#             */
/*   Updated: 2024/12/08 02:05:14 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	go_home(void)
{
	char	*path;
	char	*tmp;

	path = _env_(NULL, "HOME", NULL, SEARCH);
	if (!path || !path[0])
		return (ft_putstr_fd("cd: HOME not set\n", 2), exit_status(1, 1), 0);
	if (chdir(path) == -1)
		return (perror(path), exit_status(1, 1), 0);
	_env_(NULL, "OLDPWD", _env_(NULL, "PWD", NULL, SEARCH), CHANGE);
	tmp = getcwd(NULL, 0);
	if (tmp)
	{
		_env_(NULL, "PWD", ft_strdup(tmp), CHANGE);
		free(tmp);
	}
	return (1);
}

int	cd(char *path)
{
	char	*tmp;

	if (!path || !ft_strcmp("~", path))
		return (go_home());
	if (chdir(path) == -1)
		return (perror(path), exit_status(1, 1), 0);
	tmp = getcwd(NULL, 0);
	if (tmp)
	{
		_env_(NULL, "OLDPWD", _env_(NULL, "PWD", NULL, SEARCH), CHANGE);
		_env_(NULL, "PWD", ft_strdup(tmp), CHANGE);
		free(tmp);
	}
	return (1);
}
