/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:30:56 by ahamdi            #+#    #+#             */
/*   Updated: 2024/06/27 10:54:29 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	command_path(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = 0;
	cmd = split_command(argv);
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
	cmd = split_command(argv);
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

void	bad_argument(void)
{
	int		i;
	char	*str;
	char	*s;

	i = 0;
	str = "\tError: Bad argument\n";
	while (str[i] != '\0')
	{
		write(2, &str[i], 1);
		i++;
	}
	i = 0;
	s = "\tEx: ./pipex <file1> <cmd1> <cmd2><file2>\n";
	while (s[i] != '\0')
	{
		write(2, &s[i], 1);
		i++;
	}
}

void	filecommade(char **argv, char **envp)
{
	char	**cmd;

	if (argv[3][0] == '\0')
		errer_cmd();
	if (argv[3][0] == '/')
	{
		if (access(argv[3], X_OK) != 0)
			errer_cmd();
	}
	if (argv[3][0] == '.' && argv[3][1] == '/')
	{
		if (access(argv[3], X_OK) != 0)
			errer_cmd();
	}
}
