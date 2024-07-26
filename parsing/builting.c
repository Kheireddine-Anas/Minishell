/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 09:45:11 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/26 12:17:55 by ahamdi           ###   ########.fr       */
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

int	rediraction(t_cmd *lst_cmd, t_fd_ **fd_in_out, t_status **status)
{
	int	i;
	int	out;
	int	in;
	int	fd;

	i = 0;
	if (lst_cmd->rederaction[i])
	{
		while (lst_cmd->rederaction[i])
		{
			if (ft_strcmp("<<", lst_cmd->rederaction[i]) == 0)
			{
				(*fd_in_out)->her_doc = while_loop(&lst_cmd, fd_in_out);
				if ((*fd_in_out)->her_doc == -2)
				{
					(*status)->status = 3;
					return (2);
				}
				close((*fd_in_out)->her_doc);
				in = i;
			}
			else if (ft_strcmp("<", lst_cmd->rederaction[i]) == 0)
			{
				(*fd_in_out)->stdin = open(lst_cmd->fil_name[i], O_RDONLY);
				if ((*fd_in_out)->stdin == -1)
				{
					(*status)->status = 3;
					erro(lst_cmd->fil_name[i]);
					return (2);
				}
				close((*fd_in_out)->stdin);
				in = i;
			}
			else if (ft_strcmp(">", lst_cmd->rederaction[i]) == 0 || ft_strcmp(">>",
					lst_cmd->rederaction[i]) == 0)
			{
				if (ft_strcmp(">", lst_cmd->rederaction[i]) == 0)
					fd = open(lst_cmd->fil_name[i], O_CREAT | O_WRONLY | O_TRUNC,
							0777);
				else if (ft_strcmp(">>", lst_cmd->rederaction[i]) == 0)
					fd = open(lst_cmd->fil_name[i], O_CREAT | O_RDWR | O_APPEND,
							0777);
				if (fd == -1)
				{
					(*status)->status = 3;
					erro(lst_cmd->fil_name[i]);
					return (2);
				}
				out = i;
			}
			i++;
		}
		if (ft_strcmp("<<", lst_cmd->rederaction[in]) == 0)
		{
			(*fd_in_out)->her_doc = open("/tmp/her_doc", O_CREAT | O_RDWR,
					0777);
			if ((*fd_in_out)->her_doc == -1)
			{
				(*status)->status = 3;
				erro("her_doc");
				return (2);
			}
			dup2((*fd_in_out)->her_doc, STDIN_FILENO);
		}
		else if (ft_strcmp("<", lst_cmd->rederaction[in]) == 0)
		{
			(*fd_in_out)->stdin = open(lst_cmd->fil_name[in], O_RDONLY);
			if ((*fd_in_out)->stdin == -1)
			{
				(*status)->status = 3;
				erro(lst_cmd->fil_name[in]);
				return (2);
			}
			dup2((*fd_in_out)->stdin, STDIN_FILENO);
		}
		if (ft_strcmp(">>", lst_cmd->rederaction[out]) == 0 || ft_strcmp(">",
				lst_cmd->rederaction[out]) == 0)
		{
			if (ft_strcmp(">", lst_cmd->rederaction[out]) == 0)
				(*fd_in_out)->stdout = open(lst_cmd->fil_name[out],
						O_CREAT | O_WRONLY | O_TRUNC, 0777);
			else if (ft_strcmp(">>", lst_cmd->rederaction[out]) == 0)
				(*fd_in_out)->stdout = open(lst_cmd->fil_name[out],
						O_CREAT | O_RDWR | O_APPEND, 0777);
			if ((*fd_in_out)->stdout == -1)
			{
				(*status)->status = 3;
				erro(lst_cmd->fil_name[out]);
				return (2);
			}
			dup2((*fd_in_out)->stdout, STDOUT_FILENO);
		}
		return (3);
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
	if (lst_cmd->option && lst_cmd->option && ft_strcmp("env",
			lst_cmd->option[0]) == 0)
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
	return (0);
}
