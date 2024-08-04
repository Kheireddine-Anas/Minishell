/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_mian.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:39:55 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/03 10:05:19 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	whilloop(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
}

void	wit_process(int nb_prossuce, pid_t **pids, t_fd_ *fd_in_out, 
			t_status **status)
{
	int	j;

	j = 0;
	while (j < nb_prossuce && *pids)
	{
		if (waitpid((*pids)[j], &(*status)->status, 0) == -1)
		{
			(*status)->status = 1;
			perror("waitpid");
			return ;
		}
		j++;
	}
	(*status)->status = WEXITSTATUS((*status)->status);
	dup2(fd_in_out->fd_in, STDIN_FILENO);
	dup2(fd_in_out->fd_out, STDOUT_FILENO);
}

void	clo(int fd)
{
	if (fd > 0)
		close(fd);
}

void	close_file(t_fd_ *fd_in_out, int *fd)
{
	(void)fd;
	clo(fd_in_out->fd_out);
	clo(fd_in_out->her_doc);
	clo(fd[0]);
	clo(fd[1]);
	clo(fd_in_out->stdin);
	clo(fd_in_out->stdout);
	clo(fd_in_out->fd_in);
}

void	parent_prossuce(int *fd, t_fd_ **fd_in_out, int i, int ret_buil)
{
	if (i > 0 || ret_buil == 1)
	{
		whilloop(fd);
		close((*fd_in_out)->fd0);
		close((*fd_in_out)->fd1);
	}
	(*fd_in_out)->fd0 = fd[0];
	(*fd_in_out)->fd1 = fd[1];
}
