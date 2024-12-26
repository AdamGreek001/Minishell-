/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 06:50:10 by eel-alao          #+#    #+#             */
/*   Updated: 2024/12/25 19:56:01 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_env_char(t_env *head)
{
	char	**ret;
	char	*tmp;
	int		i;
	int		len;

	len = env_len(head);
	ret = g_malloc(sizeof(char *) * (len + 1), MALLOC);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (head->value)
		{
			tmp = ft_strjoin(head->key, "=");
			if (tmp)
				tmp = ft_strjoin(tmp, head->value);
			if (!tmp)
				return (NULL);
			ret[i++] = tmp;
		}
		head = head->next;
	}
	ret[i] = NULL;
	return (ret);
}

t_env	*add_env(t_env **head, char *key, char *value, t_call call)
{
	t_env	*tmp;
	t_env	*new;

	tmp = is_exist(*head, key);
	(call != NEW && tmp) && (tmp->hidden = false);
	if (tmp && call == ADD)
		return (tmp->value = ft_strjoin(tmp->value, value), tmp->hidden = false,
			tmp);
	if (tmp && call == NEW)
		return (tmp->value = ft_strdup(value), tmp->hidden = false, tmp);
	if (tmp && call == CHANGE)
		return (tmp->value = value, tmp->hidden = false, tmp);
	new = new_env_node(key, value);
	if (!new)
		return (NULL);
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (*head);
}

void	*del_key(t_env **head, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *head;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
		{
			if (tmp == *head)
				*head = (*head)->next;
			else
				prev->next = tmp->next;
			return (NULL);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*create_env(char **av, t_env **head)
{
	char	*key;
	char	*value;
	int		i;
	int		j;

	i = -1;
	if (!av || !*av)
		return (null_env(head));
	while (av[++i])
	{
		key = get_till_char(av[i], '=');
		if (!key)
			return (NULL);
		j = -1;
		while (av[i][++j] && av[i][j] != '=')
			;
		if (av[i][j] == '=')
			j++;
		value = ft_strdup(av[i] + j);
		if (!value)
			return (NULL);
		if (!add_env(head, key, value, NEW))
			return (NULL);
	}
	return (*head);
}

char	*get_var(t_env *head, char *key)
{
	if (!ft_strcmp(key, "?"))
		return (ft_itoa(exit_status(0, 0)));
	else if (key && !*key)
		return (ft_strdup("$"));
	while (head)
	{
		if (!ft_strcmp(key, head->key))
			return (ft_strdup(head->value));
		head = head->next;
	}
	return (ft_strdup(""));
}
