/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:10:37 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 16:09:12 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	condition_path(char *str)
{
	struct stat	file_info;

	if (access(str, F_OK))
	{
		errer_cmd(str, "No such file or directory");
		exit(127);
	}
	if (access(str, X_OK) || access(str, R_OK)
		|| access(str, W_OK))
	{
		errer_cmd(str, "Permission denied");
		exit(126);
	}
	stat(str, &file_info);
	if (S_ISDIR(file_info.st_mode))
	{
		errer_cmd(str, "is a directory");
		exit(126);
	}
}

static void	condition_file(char *str)
{
	struct stat	file_info;

	if (access(str, F_OK))
	{
		errer_cmd(str, "No such file or directory");
		exit(127);
	}
	stat(str, &file_info);
	if (S_ISDIR(file_info.st_mode))
	{
		errer_cmd(str, "is a directory");
		exit(126);
	}
}

void	filecommade(t_cmd *cmd, char **env)
{
	char		*path;

	if (!cmd)
		exit(1);
	else if (cmd->option && cmd->option[0] && cmd->option[0][0] == '\0')
		errer_cmd(cmd->option[0], "command not found");
	else if (cmd->option[0] && cmd->option[0] && cmd->option[0][0] == '/')
		condition_file(cmd->option[0]);
	else if (cmd->option[0] && cmd->option[0] && cmd->option[0][0] == '.'
		&& cmd->option[0][1] == '/')
		condition_path(cmd->option[0]);
	else if (cmd->option[0])
	{
		path = get_path(env, cmd->option[0], 0);
		if (!path)
		{
			errer_cmd(cmd->option[0], "command not found");
			exit(127);
		}
		free(path);
	}
}

void	hand_error(t_status **status, char *str)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": error\n", 2);
	(*status)->status = 1;
}
