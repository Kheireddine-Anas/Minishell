/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 09:45:11 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/27 13:10:52 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	strle_2derra(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	condition_builting(t_cmd *lst_cmd, t_env **env, t_status **status,
		t_fd_ **fd_in_out)
{
	if (lst_cmd->option && ft_strcmp("echo", lst_cmd->option[0]) == 0)
	{
		rediraction(lst_cmd, fd_in_out, status);
		cmd_echo(lst_cmd->option, status, lst_cmd);
		dup2((*fd_in_out)->fd_out, STDOUT_FILENO);
		dup2((*fd_in_out)->fd_in, STDIN_FILENO);
		return (1);
	}
	if (lst_cmd->option && ft_strcmp("export", lst_cmd->option[0]) == 0)
	{
		cmd_export(env, lst_cmd->option, status);
		return (1);
	}
	if (lst_cmd->option && ft_strcmp("exit", lst_cmd->option[0]) == 0)
	{
		cmd_exit(lst_cmd->option, status);
		return (1);
	}
	return (0);
}

int	builting(t_cmd *lst_cmd, t_env **env, t_status **status, t_fd_ **fd_in_out)
{
	if (lst_cmd->option && ft_strcmp("cd", lst_cmd->option[0]) == 0)
	{
		if (rediraction(lst_cmd, fd_in_out, status) == 2)
			return (1);
		(*status)->status = 0;
		cmd_cd(lst_cmd->option, env, status);
		return (1);
	}
	if (lst_cmd->option && ft_strcmp("env", lst_cmd->option[0]) == 0)
	{
		(*status)->status = 0;
		print_env(*env);
		return (1);
	}
	if (lst_cmd->option && ft_strcmp("unset", lst_cmd->option[0]) == 0)
	{
		if (!lst_cmd->option[1])
			return (1);
		(*status)->status = 0;
		cmd_unset(env, lst_cmd->option[1]);
		return (1);
	}
	if (condition_builting(lst_cmd, env, status, fd_in_out) == 1)
		return (1);
	return (0);
}
