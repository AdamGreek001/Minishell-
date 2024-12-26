/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:42:22 by akharfat          #+#    #+#             */
/*   Updated: 2024/12/26 16:42:23 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			hidden;
	int				tmp;
	struct s_env	*next;
}	t_env;

typedef struct s_exec
{
	char			*cmd;
	char			**opt;
	int				fd_out;
	int				fd_in;
	bool			run_it;
	struct s_exec	*next;
}	t_exec;

typedef enum s_call
{
	INIT,
	NEW,
	ADD,
	CHANGE,
	SEARCH,
	REMOVE,
	PRINT_XPRT,
	GET_STRCT,
	GET_CHAR
}	t_call;

typedef enum s_token
{
	WORD,
	SGL_Q,
	DBL_Q,
	PIPE,
	R_OUT,
	R_IN,
	HRDC,
	APND
}	t_token;

typedef struct s_list
{
	char			*token;
	char			*old;
	t_token			type;
	bool			spc_after;
	bool			spc_before;
	bool			split_it;
	int				hrdc_fd;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

#endif