/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 06:50:05 by eel-alao          #+#    #+#             */
/*   Updated: 2024/12/08 06:50:06 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*is_exist(t_env *head, char *key)
{
	while (head)
	{
		if (!ft_strcmp(key, head->key))
			return (head);
		head = head->next;
	}
	return (NULL);
}

void	*_env_(char **env, char *key, char *value, t_call call)
{
	static t_env	*head;

	if (call == GET_STRCT)
		return (head);
	else if (call == INIT)
		return (create_env(env, &head));
	else if (call >= 1 && call <= 3)
		return (add_env(&head, key, value, call));
	else if (call == SEARCH)
		return (get_var(head, key));
	else if (call == REMOVE)
		return (del_key(&head, key));
	else if (call == GET_CHAR)
		return (get_env_char(head));
	return (NULL);
}
