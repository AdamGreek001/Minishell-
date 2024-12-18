/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_collector.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 11:42:21 by akharfat          #+#    #+#             */
/*   Updated: 2024/12/08 12:53:24 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_COLLECTOR_H
# define G_COLLECTOR_H
# include <stdlib.h>

typedef struct s_col
{
	void			*ptr;
	struct s_col	*next;
}	t_col;

typedef enum e_gc
{
	FREE,
	MALLOC
}	t_gc;

void	*g_malloc(size_t size, t_gc call);

#endif