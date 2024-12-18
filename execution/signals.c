/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 02:05:40 by eel-alao          #+#    #+#             */
/*   Updated: 2024/12/15 12:31:30 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	while (s[++i])
		write(fd, &s[i], 1);
	return (1);
}

void	sig_hand(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	set_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sig_hand);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

void	child_sig(int sig)
{
	(void)sig;
	if (waitpid(-1, NULL, WNOHANG) == -1)
	{
		ft_putstr_fd("\n", 1);
	}
}
