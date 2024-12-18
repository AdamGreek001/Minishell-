/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharfat <akharfat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:48:02 by akharfat          #+#    #+#             */
/*   Updated: 2024/12/08 12:38:49 by akharfat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "struct.h"
# include <errno.h>
# include "garbage_collector/g_collector.h"

# define SPACES "\t\n\v\f\r "

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_isalnum(int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_itoa(int n);
int		ft_toupper(int c);
int		ft_isalpha(int c);
t_env	*new_env(char *key, char *value);
char	**ft_split(const char *str, char spliter);
int		exec(t_list *msh, int p_count);
t_exec	*setup_exec_list(t_list *s, int *p_count);
bool	is_reder(int type);
int		set_fd(t_exec *s, int reder_type, char *file);
char	**get_char_env(char **envv, int set);
int		pipe_count(t_exec *h);
bool	is_built(char *cmd);
int		exit_status(int _sts, int set);
int		ft_putstrs(char *s1, char *s2, char *s3, int fd);
int		check_cmd_slash(char *cmd);
int		get_path(t_exec *s);
int		exec_cmd(t_exec *s, int p_count);
int		set_signals(void);
void	sig_hand(int sig);
void	child_sig(int sig);
int		ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		builtin_nf(t_exec *node);
int		echo(t_exec *node, int fd);
int		my_exit(t_exec *node);
char	*get_till_char(char *str, char c);
void	*_env_(char **env, char *key, char *value, t_call call);
void	prnt_env(int fd);
int		disp_exprt(int fd);
t_env	*add_env(t_env **head, char *key, char *value, t_call call);
int		cd(char *path);
int		pwd(int fd);
int		env_len(t_env *node);
t_env	*new_env_node(char *key, char *value);
t_env	*copy_node(t_env *node);
t_env	*null_env(t_env **head);
char	**get_env_char(t_env *head);
void	*change_var(t_env *head, char *key, char *value);
void	*del_key(t_env **head, char *key);
t_env	*add_env(t_env **head, char *key, char *value, t_call call);
char	*get_var(t_env *head, char *key);
t_env	*create_env(char **av, t_env **head);
t_env	*is_exist(t_env *head, char *key);
char	**fill_opts(t_list **s, t_exec *new, int i);
int		ft_isspace(char c);
char	*ft_join_char(char *s, char c);
char	*expand(char *s);
t_list	*parce_line(char *line);
int		count_w(char const *s, char *del);
char	**pool_split(char const *s, char *del);
int		heredoc(char *delim, t_list *node, t_token del_type);
t_list	*new_node(char *tkn, char char_after, char qut);
bool	is_built(char *cmd);
int		exprt_err(char *var, t_call *call);
int		unst_err(char *var);
bool	check_key(char *key);
int		check_qut_syntax(char *line, char qut);
char	*get_quoted(char *line, char c, int *i);
bool	is_token(char *line);
char	*get_token(char *line, int *i);
bool	is_char_token(char c);
char	*get_word(char *line, int *i);
t_token	get_type(char *token);
int		add_node_back(t_list **head, t_list *new);
t_list	*new_node(char *tkn, char char_after, char qut);
bool	both_reder(t_token t1, t_token t2);
t_list	*syntax_err(void);
char	*get_old(char *cur, char *next, t_token next_type);
int		join_nodes(t_list *head);
int		builtin_f(t_exec *node);
char	*check_expand(char *tkn, t_list *node, char qut);

#endif