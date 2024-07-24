/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:46:31 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/23 18:24:31 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	child_process(t_cmd *cmd, char **envp, int *fd, t_fd_ **fd_in_out)
{
	if (!cmd || !envp)
		error_ch(cmd->option[0]);
	if (cmd->single > 0 || cmd->double_q > 0)
	{
		ft_putstr_fd("\033[34minishell: ", 2);
		ft_putstr_fd("syntax error : error in quot\033[0m\n", 2);
		exit(1);
	}
	if ((*fd_in_out)->retu_red != 3)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
	}
	exe_cmd(cmd, envp);
}

void	fin_commande(t_cmd *cmd, char **envp)
{
	if (!cmd || !envp)
	{
		errer_cmd(cmd->option[0]);
		return ;
	}
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
