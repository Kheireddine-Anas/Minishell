/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:43:15 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/29 14:10:47 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*set_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_calloc(i + 1, sizeof(char));
	i = -1;
	while (str[++i] && str[i] != '=')
		name[i] = str[i];
	name[i] = '\0';
	return (name);
}

char	*set_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (ft_strdup(""));
	value = ft_calloc((ft_strlen(str) - i), sizeof(char));
	i++;
	while (str[i])
		value[j++] = str[i++];
	value[j] = '\0';
	return (value);
}

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


void	add_exp(t_env *env, char *value, char *var)
{
	while (env)
	{
		if (!ft_strcmp(env->key, var))
		{
			free(var);
			var = set_value(value);
			if (var)
			{
				free(env->value);
				env->value = var;
			}
			break ;
		}
		if (!env->next)
		{
			env->next = seenv_t(value);
			break ;
		}
		env = env->next;
	}
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
			add_exp(tmp, value[i], var);
		else
		{
			ft_putstr_fd("mini-shell: ", 2);
			ft_putstr_fd(value[i], 2);
			ft_putendl_fd(": not a valid identifier", 2);
			(*status)->status = 1;
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
