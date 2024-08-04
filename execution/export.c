/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:43:15 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/03 14:38:43 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*seenv_t(char *str)
{
	t_env	*head;

	head = ft_calloc(1, sizeof(t_env));
	head->key = set_name(str);
	head->value = set_value(str);
	head->next = NULL;
	return (head);
}

void	show_exp(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!(tmp->value))
			printf("declare -x %s\n", tmp->key);
		else
			printf("declare -x %s =\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int	check_exp(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]) || name[0] == '=')
		return (1);
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]))
			return (1);
		i++;
	}
	return (0);
}

int	export_add(t_env **env, char **value, t_status **status)
{
	int		i;
	char	*var;
	t_env	*tmp;

	tmp = *env;
	i = 1;
	while (value[i])
	{
		var = set_name(value[i]);
		if (!check_exp(value[i]))
		{
			add_exp(tmp, value[i], var);
			free(var);
		}
		else
		{
			free(var);
			error_export(status, value[i]);
			return (1);
		}
		i++;
	}
	(*status)->status = 0;
	return (0);
}

int	cmd_export(t_env **env, char **add, t_status **status)
{
	if (!add[1])
		show_exp(*env);
	else
	{
		if (export_add(env, add, status) == 1)
			return (1);
	}
	return (0);
}
