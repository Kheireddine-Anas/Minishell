/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:54:23 by ahamdi            #+#    #+#             */
/*   Updated: 2024/06/27 10:56:58 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char **envp, char *cmd, int i)
{
	char	*path_new;
	char	*path;
	char	**path_split;

	path_new = NULL;
	path = NULL;
	while (envp[i++])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) != NULL)
		{
			path = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) + 5; 
			break ;
		}
	}
	i = 0;
	path_split = ft_split(path, ':');
	{
		if (!path_split)
			exit(1);
	}
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

void	commad_path(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = 0;
	cmd = split_double_qot(argv,envp);
	if(!cmd)
		exit(1);
	path = cmd[0];
	if (!path)
	{
		i = 0;
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
	}
	if (execve(path, cmd, envp) == -1)
	{
		perror("Bad command");
		exit(0);
	}
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = 0;
	cmd = split_double_qot(argv,envp);
	path = get_path(envp, cmd[0], i);
	if (!path)
	{
		i = 0;
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
	}
	if (execve(path, cmd, envp) == -1)
	{
		perror("Bad command");
		exit(0);
	}
}

void	run_script(char *script_path, char **envp)
{
	char	**cmd;

	cmd = malloc(2 * sizeof(char *));
	if (!cmd)
		exit(1);
	cmd[0] = script_path;
	cmd[1] = NULL;
	if (execve(script_path, cmd, envp) == -1)
	{
		perror("Bad command");
		exit(0);
	}
}
