/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:43:37 by akharfat          #+#    #+#             */
/*   Updated: 2024/12/25 20:18:49 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	_env_(env, NULL, NULL, INIT);
	set_signals();
	return (1);
}

// int close_fds()

int	main(int ac, char **av, char **env)
{
	t_list	*head;
	char	*line;
	int		p_count;
	int		in;

	start(ac, av, env);
	while (1)
	{
		p_count = 0;
		line = readline("minishell> ");
		if (!line)
			break ;
		in = dup(0);
		head = parce_line(line);
		if (head && read(0, NULL, 0) != -1)
			exec(head, p_count);
		new_node(NULL, '\n', '\r');
		if (line[0])
			add_history(line);
		free(line);
		(1) && (dup2(in, 0), close(in));
	}
	g_malloc(0, FREE);
	return (exit_status(0, 0));
}
