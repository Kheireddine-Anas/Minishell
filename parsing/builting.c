/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 09:45:11 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/30 10:14:48 by ahamdi           ###   ########.fr       */
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

static int	condition_builting(t_cmd *lst_cmd, t_env **env, t_status **status)
{
	if (lst_cmd->option && ft_strcmp("echo", lst_cmd->option[0]) == 0)
	{
		cmd_echo(lst_cmd->option, status, lst_cmd);
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
	else if (lst_cmd->option && ft_strcmp("pwd", lst_cmd->option[0]) == 0)
	{
		cmd_pwd();
		return (1);
	}
	return (0);
}

int	builting(t_cmd *lst_cmd, t_env **env, t_status **status, t_fd_ **fd_in_out)
{
	(*fd_in_out)->retu_red = rediraction(lst_cmd, fd_in_out, status);
	if ((*fd_in_out)->retu_red == 2)
	{
		close_file((*fd_in_out), (*fd_in_out)->fd);
		return (1);
	}
	if (lst_cmd->option && ft_strcmp("cd", lst_cmd->option[0]) == 0)
	{
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
	if (condition_builting(lst_cmd, env, status) == 1)
		return (1);
	return (0);
}
