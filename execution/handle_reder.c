/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_reder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 02:05:31 by eel-alao          #+#    #+#             */
/*   Updated: 2024/12/24 23:36:59 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(int type, char *file)
{
	if (type == R_IN)
		return (open(file, O_RDONLY));
	else if (type == APND)
		return (open(file, O_CREAT | O_WRONLY | O_APPEND), 0644);
	else
		return (open(file, O_CREAT | O_WRONLY | O_TRUNC), 0644);
}

int	set_fd(t_exec *s, int reder_type, char *file)
{
	int	fd;

	if (!s->run_it)
		return (1);
	fd = open_file(reder_type, file);
	if (fd == -1)
	{
		perror(file);
		exit_status(1, 1);
		return (s->run_it = false, 0);
	}
	if (reder_type == R_IN && s->fd_in == 0)
		s->fd_in = fd;
	else if (reder_type == R_IN)
		(1) && (close(s->fd_in), s->fd_in = fd);
	else if (s->fd_out != 1)
		close(s->fd_out);
	if (reder_type != R_IN)
		s->fd_out = fd;
	return (1);
}
