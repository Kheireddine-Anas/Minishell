/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utul_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:51:21 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/03 14:40:22 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exe_cmd(t_cmd *cmd, char **envp)
{
	if (!cmd || !envp)
		return ;
	if (cmd && cmd->option && cmd->option[0][0] == '/')
		commad_path(cmd, envp);
	else if (cmd && cmd->option && cmd->option[0][0] == '.'
		&& cmd->option[0][1] == '/')
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

void	chek_child_processus(char *lim, int fd)
{
	char	*str;
	char	*strj;

	strj = ft_strjoin(lim, "\n");
	while (1)
	{
		signal(SIGINT, handle_sigint_herdoc);
		ft_putstr_fd("here_doc> ", 0);
		str = get_next_line(STDIN_FILENO);
		if (!str || !ft_strncmp(strj, str, ft_strlen(str)))
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, fd);
		free(str);
	}
	free(strj);
	exit(0);
}
