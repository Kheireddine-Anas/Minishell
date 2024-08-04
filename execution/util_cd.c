/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:10:57 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/03 14:42:50 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_valus(t_env *envs, char *srch)
{
	t_env	*tmp;

	tmp = envs;
	while (tmp)
	{
		if (!(strcmp(tmp->key, srch)))
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	cmd_pwd(char **str, t_status **status)
{
	char	*pwd;

	if (str[1] && ft_strcmp(str[1], "oi") != 0)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		(*status)->status = 1;
		return (1);
	}
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
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

void	error_export(t_status **status, char *str)
{
	ft_putstr_fd("mini-shell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": not a valid identifier", 2);
	(*status)->status = 1;
}

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
