/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:42:39 by akharfat          #+#    #+#             */
/*   Updated: 2024/12/15 11:46:23 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_hrdc_file(t_list *node)
{
	char	*file;
	char	*tmp;
	int		fd;

	tmp = malloc(1);
	if (!tmp)
		return (-1);
	file = ft_itoa((int)tmp);
	(file) && (file = ft_strjoin("/tmp/.tmp", file));
	if (!file)
		return (free(tmp), -1);
	fd = open(file, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return (free(tmp), fd);
	node->hrdc_fd = open(file, O_RDONLY);
	if (node->hrdc_fd == -1)
		return (free(tmp), close(fd), node->hrdc_fd);
	unlink(file);
	return (free(tmp), fd);
}

void	hrdc_sig(int sig)
{
	(void)sig;
	exit_status(1, 1);
	close(0);
}

char	*cust_strdup(char *s)
{
	char	*ret;

	if (!s)
		return (NULL);
	ret = ft_strdup(s);
	if (!ret)
		return (NULL);
	return (free(s), ret);
}

int	heredoc(char *delim, t_list *node, t_token del_type)
{
	int		fd;
	char	*line;

	(1) && (fd = get_hrdc_file(node));
	if (fd == -1)
		return (0);
	signal(SIGINT, hrdc_sig);
	while (1)
	{
		line = cust_strdup(readline("> "));
		if (!line)
			break ;
		if (!ft_strcmp(line, delim))
			break ;
		if (del_type == WORD)
			line = expand(line);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	signal(SIGINT, sig_hand);
	return (close(fd), 1);
}