/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:49:47 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/03 15:09:31 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*last_f(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	size_(t_env *lst)
{
	t_env	*help;
	int		len;

	len = 0;
	help = lst;
	while (help != NULL)
	{
		help = help->next;
		len++;
	}
	return (len);
}

static void	add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!*lst)
	{
		*lst = new;
	}
	else
	{
		last = last_f(*lst);
		last->next = new;
	}
}

static t_env	*get_env_data(char *envp)
{
	t_env	*noud;

	noud = NULL;
	if (!envp)
		return (NULL);
	noud = malloc(sizeof(t_env));
	if (noud == NULL)
		return (NULL);
	else
	{
		noud->value = ft_strdup(ft_strchr(envp, '=') + 1);
		noud->key = ft_substr(envp, 0, ft_strlen(envp) - ft_strlen(noud->value)
				- 1);
		noud->next = NULL;
	}
	return (noud);
}

t_env	*get_env(char **envp)
{
	int		i;
	t_env	*env;

	env = NULL;
	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		add_back(&env, get_env_data(envp[i]));
		i++;
	}
	return (env);
}
