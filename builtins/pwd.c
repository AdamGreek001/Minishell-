/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:27:25 by akharfat          #+#    #+#             */
/*   Updated: 2024/12/26 16:37:37 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(int fd)
{
	char	*cur;

	cur = getcwd(NULL, 0);
	if (!cur)
	{
		cur = _env_(NULL, "PWD", NULL, SEARCH);
		if (!cur || !cur[0])
		{
			perror("pwd");
			exit_status(1, 1);
			return (0);
		}
		ft_putstr_fd(cur, fd);
		ft_putstr_fd("\n", fd);
	}
	else
	{
		ft_putstr_fd(cur, fd);
		ft_putstr_fd("\n", fd);
		free(cur);
	}
	return (1);
}
