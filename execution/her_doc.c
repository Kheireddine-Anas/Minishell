/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:45:29 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/03 14:40:56 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	while_loop(char *lim, t_fd_ **fd_in_out, t_status **status)
{
	int		fd;
	pid_t	c;

	dup2((*fd_in_out)->fd_in, STDIN_FILENO);
	dup2((*fd_in_out)->fd_out, STDOUT_FILENO);
	fd = open("/tmp/her_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
	{
		erro("/tmp/her_doc");
		return (-2);
	}
	c = fork();
	if (c == -1)
		hand_error(status, "fork");
	if (c == 0)
		chek_child_processus(lim, fd);
	else if (c > 0)
		waitpid(c, &(*status)->status, 0);
	return (fd);
}

static int	chek_her_rediraction(t_cmd *temp, t_fd_ **fd_in_out,
		t_status **status, int i)
{
	if (ft_strcmp("<<", temp->rederaction[i]) == 0)
	{
		(*fd_in_out)->her_doc = while_loop(temp->fil_name[i], fd_in_out,
				status);
		if ((*fd_in_out)->her_doc == -2)
		{
			(*status)->status = 3;
			return (2);
		}
	}
	return (0);
}

int	chek_her_doc(t_cmd *lst_cmd, t_fd_ **fd_in_out, t_status **status)
{
	t_cmd	*temp;
	int		i;

	if (!lst_cmd || !*fd_in_out)
		return (2);
	temp = lst_cmd;
	while (temp)
	{
		i = 0;
		while (temp->rederaction[i])
		{
			if (chek_her_rediraction(temp, fd_in_out, status, i) == 2)
				return (2);
			close((*fd_in_out)->her_doc);
			(*fd_in_out)->her_doc = -2;
			i++;
		}
		temp = temp->next;
	}
	return (0);
}

void	handle(int sig)
{
	if (sig == SIGQUIT)
	{
		signal(SIGQUIT, SIG_DFL);
		printf ("Quit: 3\n");
	}
}

int	whillop(t_cmd **lst_cmd, t_fd_ *fd_in_out, t_status **status, int *i)
{
	int	ret;

	ret = 0;
	if (pipe(fd_in_out->fd) == -1)
		hand_error(status, "pipe");
	fd_in_out->pids[*i] = fork();
	if (fd_in_out->pids[*i] == -1)
		hand_error(status, "fork");
	if (fd_in_out->pids[*i] == 0)
	{
		signal(SIGQUIT, handle);
		if (*lst_cmd != fd_in_out->last)
			child_process(*lst_cmd, fd_in_out->envp, &fd_in_out, status);
		else if (*lst_cmd == fd_in_out->last)
			fin_commande(*lst_cmd, fd_in_out->envp, status, &fd_in_out);
	}
	else if (fd_in_out->pids[*i] > 0)
		parent_prossuce(fd_in_out->fd, &fd_in_out, *i, ret);
	whilloop(fd_in_out->fd);
	(*i)++;
	return (0);
}
