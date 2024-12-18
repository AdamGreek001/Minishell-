/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 06:50:12 by eel-alao          #+#    #+#             */
/*   Updated: 2024/12/08 06:51:54 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_len(t_env *node)
{
	int	i;

	i = 0;
	while (node)
	{
		if (node->value)
			i++;
		node = node->next;
	}
	return (i);
}

t_env	*new_env_node(char *key, char *value)
{
	t_env	*new;

	new = g_malloc(sizeof(t_env), MALLOC);
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->hidden = false;
	if (!value || !ft_strcmp(key, "_"))
		new->hidden = true;
	new->next = NULL;
	return (new);
}

t_env	*copy_node(t_env *node)
{
	t_env	*new;

	new = g_malloc(sizeof(t_env), MALLOC);
	if (!new)
		return (NULL);
	new->hidden = node->hidden;
	new->key = ft_strdup(node->key);
	if (!node->value)
	{
		new->value = NULL;
		new->hidden = true;
	}
	else
		new->value = ft_strdup(node->value);
	new->next = NULL;
	return (new);
}

t_env	*null_env(t_env **head)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (NULL);
	if (!add_env(head, ft_strdup("PATH"),
			ft_strdup("/usr/local/sbin:/usr/local/bin:"
				"/usr/sbin:/usr/bin:/sbin:/bin"),
			NEW))
		return (free(path), NULL);
	if (!add_env(head, "PWD", ft_strdup(path), NEW))
		return (free(path), NULL);
	free(path);
	if (!add_env(head, ft_strdup("SHLVL"), ft_strdup("1"), NEW))
		return (NULL);
	if (!add_env(head, ft_strdup("_"), ft_strdup("/usr/bin/env"), NEW))
		return (NULL);
	if (!add_env(head, ft_strdup("OLDPWD"), NULL, NEW))
		return (NULL);
	return (*head);
}

void	*change_var(t_env *head, char *key, char *value)
{
	while (head)
	{
		if (!ft_strcmp(key, head->key))
			return (head->value = value, NULL);
		head = head->next;
	}
	return (NULL);
}
