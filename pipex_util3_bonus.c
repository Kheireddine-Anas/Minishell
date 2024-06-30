/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util3_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:21:19 by ahamdi            #+#    #+#             */
/*   Updated: 2024/03/29 16:46:40 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	wit_process(int argc, pid_t **pids,int fd0, int fd1)
{
	int	j;

	j = 0;
	while (j < argc)
	{
		waitpid((*pids)[j], NULL, 0);
		j++;
	}
	free(*pids);
	dup2(fd0, STDIN_FILENO);
	dup2(fd1, STDOUT_FILENO);
}

void	whilloop(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
}

void	erro(void)
{
	perror("Error in pipe or process");
	exit(3);
}

void	errer_cmd(void)
{
	perror("invalide command");
	exit(127);
}

void	filecommade(char **argv,int i)
{
	if (!argv)
		errer_cmd();
	if (argv[i -1][0] == '\0')
		errer_cmd();
	if (argv[i - 1][0] == '/')
	{
		if (access(argv[i - 1], X_OK) != 0)
			errer_cmd();
	}
	if (argv[i - 1][0] == '.' && argv[i - 1][1] == '/')
	{
		if (access(argv[i - 1], X_OK) != 0)
			errer_cmd();
	}
}
