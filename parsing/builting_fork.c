/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:32:49 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/03 11:46:49 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chke_builting(char *str)
{
	if (ft_strcmp("echo", str) == 0 || ft_strcmp("export", str) == 0
		|| ft_strcmp("exit", str) == 0 || ft_strcmp("cd", str) == 0
		|| ft_strcmp("env", str) == 0 || ft_strcmp("unset", str) == 0
		|| ft_strcmp("pwd", str) == 0)
		return (1);
	else
		return (0);
}

static void	condition_builting(t_cmd *lst_cmd, t_env **env, t_status **status)
{
	if (lst_cmd->option && ft_strcmp("echo", lst_cmd->option[0]) == 0)
	{
		if (cmd_echo(lst_cmd->option, status, lst_cmd) == 1)
			exit(1);
		exit(0);
	}
	else if (lst_cmd->option && ft_strcmp("export", lst_cmd->option[0]) == 0)
	{
		if (cmd_export(env, lst_cmd->option, status))
			exit(1);
		exit(0);
	}
	else if (lst_cmd->option && ft_strcmp("exit", lst_cmd->option[0]) == 0)
	{
		cmd_exit(lst_cmd->option, status);
		exit(0);
	}
	else if (lst_cmd->option && ft_strcmp("pwd", lst_cmd->option[0]) == 0)
	{
		if (cmd_pwd(lst_cmd->option, status) == 1)
			exit(1);
		exit(0);
	}
}

void	builting_fork(t_cmd *lst_cmd, t_env **env, t_status **status,
		t_fd_ *fd_in_out)
{
	if (lst_cmd != fd_in_out->last && fd_in_out->retu_red != 3)
	{
		dup2(fd_in_out->fd[1], STDOUT_FILENO);
		close(fd_in_out->fd[0]);
	}
	if (lst_cmd->option && ft_strcmp("cd", lst_cmd->option[0]) == 0)
	{
		if (cmd_cd(lst_cmd->option, env, status) == 1)
			exit(1);
		exit(0);
	}
	else if (lst_cmd->option && ft_strcmp("env", lst_cmd->option[0]) == 0)
	{
		if (print_env(*env) == 1)
			exit(1);
		exit(0);
	}
	else if (lst_cmd->option && ft_strcmp("unset", lst_cmd->option[0]) == 0)
	{
		if (!lst_cmd->option[1])
			exit(1);
		cmd_unset(env, lst_cmd->option[1]);
		exit(0);
	}
	condition_builting(lst_cmd, env, status);
}
