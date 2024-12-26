/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:27:25 by akharfat          #+#    #+#             */
/*   Updated: 2024/12/26 16:38:09 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_putstrs(char *s1, char *s2, char *s3, int fd)
{
	if (s1)
		write(fd, s1, ft_strlen(s1));
	if (s2)
		write(fd, s2, ft_strlen(s2));
	if (s3)
		write(fd, s3, ft_strlen(s3));
	return (1);
}

int	check_cmd_slash(char *cmd)
{
	if (access(cmd, X_OK | F_OK) == -1)
		return (perror(cmd), exit(127), 0);
	return (1);
}

int	get_path(t_exec *s)
{
	char	**pth;
	int		i;
	char	*tmp;
	char	*cmd;

	(1) && (i = -1, cmd = s->cmd);
	if (!cmd)
		return (0);
	if (ft_strchr(cmd, '/'))
		return (check_cmd_slash(cmd));
	pth = ft_split(_env_(NULL, "PATH", NULL, SEARCH), ':');
	if (!pth)
		return (0);
	while (pth[++i] && cmd[0])
	{
		tmp = ft_strjoin(pth[i], "/");
		if (tmp)
			tmp = ft_strjoin(tmp, cmd);
		if (!tmp)
			return (0);
		if (access(tmp, X_OK | F_OK) != -1)
			return (s->cmd = tmp, 1);
	}
	return (ft_putstrs(cmd, ": command not found", "\n", 2), exit(127), 0);
}
