/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 02:05:24 by eel-alao          #+#    #+#             */
/*   Updated: 2024/12/15 12:09:06 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_work(t_exec *head, int *fd)
{
	char	**env;

	if (head->next)
		(1) && (dup2(fd[1], 1), close(fd[0]), close(fd[1]));
	if (head->fd_in != 0)
		(1) && (dup2(head->fd_in, 0), close(head->fd_in));
	if (head->fd_out != 1)
		(1) && (dup2(head->fd_out, 1), close(head->fd_out));
	if (!head->run_it)
		exit(errno);
	if (is_built(head->cmd))
	{
		builtin_f(head);
		exit(exit_status(0, 0));
	}
	env = (char **)_env_(NULL, NULL, NULL, GET_CHAR);
	if (get_path(head))
	{
		execve(head->cmd, head->opt, env);
		perror(head->cmd);
	}
	exit(errno);
	return (1);
}

int	wait_child(int in)
{
	int	status;

	while (wait(&status) != -1)
	{
		if (WIFEXITED(status))
			exit_status(WEXITSTATUS(status), 1);
		else
			exit_status(WTERMSIG(status) | 128, 1);
	}
	signal(SIGINT, sig_hand);
	signal(SIGQUIT, SIG_IGN);
	return (dup2(in, 0), close(in), 1);
}

int	innit_exec(int p_count, int *fd)
{
	signal(SIGINT, child_sig);
	signal(SIGQUIT, child_sig);
	if (p_count - 1 > 0)
		return (pipe(fd));
	return (1);
}

void	parent_work(t_exec **head, int *fd)
{
	if ((*head)->next)
		dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	if ((*head)->fd_in != 0)
		close((*head)->fd_in);
	if ((*head)->fd_out != 1)
		close((*head)->fd_out);
	*head = (*head)->next;
}

int	exec(t_list *msh, int p_count)
{
	t_exec	*head;
	int		pid;
	int		fd[2];
	int		in;

	in = dup(0);
	head = setup_exec_list(msh, &p_count);
	if (!head)
		return (close(in), 0);
	if (!head->next && is_built(head->cmd))
		return (close(in), builtin_nf(head));
	while (head)
	{
		if (innit_exec(p_count, fd) == -1)
			return (perror("pipe()"), close(in), 0);
		pid = fork();
		if (pid == -1)
			return (perror("fork()"), close(fd[0]), close(fd[1]), dup2(in, 0),
				close(in), 0);
		if (pid == 0)
			exec_work(head, fd);
		if (pid > 0)
			parent_work(&head, fd);
	}
	return (wait_child(in), 1);
}
