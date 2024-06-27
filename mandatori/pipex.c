/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:55:14 by ahamdi            #+#    #+#             */
/*   Updated: 2024/06/27 10:48:07 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		perror("Bad ***command");
		exit(0);
	}
}

char	*get_path(char **envp, char *cmd, int i)
{
	char	*path_new;
	char	*path;
	char	**path_split;

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
	while (path_split[i])
	{
		path_split[i] = ft_strjoin(ft_strjoin(path_split[i], "/"), cmd);
		if (access(path_split[i], X_OK) == 0)
		{
			path_new = path_split[i];
			break ;
		}
		i++;
	}
	return (path_new);
}

static void	child(char **argv, char **envp, int *fd, int filein)
{
	if (argv[2][0] == '\0')
	{
		perror("invalide command");
		exit(0);
	}
	dup2(filein, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	if (argv[2][0] == '/')
		command_path(argv[2], envp);
	else if (argv[2][0] == '.' && argv[2][1] == '/')
		run_script(argv[2], envp);
	else
		execute(argv[2], envp);
}

static void	parent(int *fd, char **argv, char **envp, pid_t pid)
{
	int		fileout;
	pid_t	pid1;

	filecommade(argv, envp);
	pid1 = fork();
	if (pid1 == -1)
		erro();
	if (pid1 == 0)
	{
		fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fileout == -1)
			erro_file();
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		dup2(fileout, STDOUT_FILENO);
		if (argv[3][0] == '/')
			command_path(argv[3], envp);
		else if (argv[3][0] == '.' && argv[3][1] == '/')
			run_script(argv[3], envp);
		else
			execute(argv[3], envp);
	}
	else
		wit_process(fd, pid, pid1);
}

int	main(int argc, char *argv[], char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		filein;

	if (argc == 5)
	{
		filein = open(argv[1], O_RDONLY);
		if (filein == -1)
			erro_file();
		if (pipe(fd) == -1)
			erro();
		pid = fork();
		if (pid == -1)
			erro();
		if (pid == 0)
			child(argv, envp, fd, filein);
		else
		{
			parent(fd, argv, envp, pid);
		}
	}
	else
		bad_argument();
}
