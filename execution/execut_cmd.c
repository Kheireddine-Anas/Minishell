/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:46:31 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/02 10:59:34 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	child_process(t_cmd *cmd, char **envp, t_fd_ **fd_in_out, t_status **status)
{
	if (!cmd || !envp)
		error_ch(cmd->option[0]);
	(*fd_in_out)->retu_red = rediraction(cmd, fd_in_out, status);
	if ((*fd_in_out)->retu_red == 2)
		exit(1);
	if (!(*cmd->option))
		exit(0);
	if (cmd->option && chke_builting(cmd->option[0]) == 1)
		builting_fork(cmd, &(*fd_in_out)->env, status, *fd_in_out);
	if ((*fd_in_out)->retu_red != 3)
	{
		dup2((*fd_in_out)->fd[1], STDOUT_FILENO);
		close((*fd_in_out)->fd[0]);
	}
	exe_cmd(cmd, envp);
}

void	fin_commande(t_cmd *cmd, char **envp, t_status **status, t_fd_ **fd_in_out)
{
	if (!cmd || !envp)
	{
		errer_cmd(cmd->option[0], "command not found");
		exit (127);
	}
	(*fd_in_out)->retu_red = rediraction(cmd, fd_in_out, status);
	if ((*fd_in_out)->retu_red == 2)
		exit(1);
	if (!(*cmd->option))
		exit(0);
	if (cmd->option && chke_builting(cmd->option[0]) == 1)
		builting_fork(cmd, &(*fd_in_out)->env, status, *fd_in_out);
	filecommade(cmd, envp);
	exe_cmd(cmd, envp);
}

int	chek_herdoc(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i + 1])
	{
		if ((str[i] == '<' && str[i +1] == '<') 
			|| (str[i] == '>' && str[i +1] == '>'))
			return (1);
		i++;
	}
	return (0);
}
