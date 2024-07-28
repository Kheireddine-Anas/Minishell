/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utul_rederaction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:51:21 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/20 10:49:31 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_cmd(t_cmd *cmd, char **envp)
{
	if (cmd->option[0][0] == '/')
		commad_path(cmd, envp);
	else if (cmd->option[0][0] == '.' && cmd->option[0][1] == '/')
	{
		if (execve(cmd->option[0], cmd->option, envp) == -1)
			error_ch(cmd->option[0]);
	}
	else
		execute(cmd, envp);
}

void	cmd_unset(t_env **env, char *var)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (strcmp(tmp->key, var) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	update_env(t_env **env, char *var, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (strcmp(tmp->key, var) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}
