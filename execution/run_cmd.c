/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:51:57 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/30 17:41:05 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_executable_path(char **path_split, char *cmd)
{
	char	*path_new;
	int		i;

	i = 0;
	path_new = NULL;
	while (path_split[i])
	{
		path_split[i] = strjoi(path_split[i], "/", cmd);
		if (access(path_split[i], X_OK) == 0)
		{
			path_new = path_split[i];
			break ;
		}
		i++;
	}
	return (path_new);
}

char	*get_path(char **envp, char *cmd, int i)
{
	char	*path_new;
	char	*path;
	char	**path_split;

	path_new = NULL;
	path = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) != NULL)
		{
			path = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) + 5; 
			break ;
		}
		i++;
	}
	if (!path)
		return (NULL);
	path_split = ft_split(path, ':');
	if (!path_split)
		return (NULL);
	path_new = find_executable_path(path_split, cmd);
	return (path_new);
}

void	commad_path(t_cmd *cmd, char **envp)
{
	char	*path;

	if (!cmd || !cmd->option)
		return ;
	path = cmd->option[0];
	if (execve(path, cmd->option, envp) == -1)
		error_ch(cmd->option[0]);
}

void	execute(t_cmd	*cmd, char **envp)
{
	char	*path;

	if (!cmd || !cmd->option)
		return ;
	path = get_path(envp, cmd->option[0], 0);
	if (execve(path, cmd->option, envp) == -1)
		error_ch(cmd->option[0]);
}
