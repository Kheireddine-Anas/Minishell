/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eroor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:52:46 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/02 09:28:57 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_alocation(void)
{
	perror("Allocation error");
	exit(1);
}

void	errer_cmd(char *str, char *ms_err)
{
	ft_putstr_fd("\033[31mminishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(ms_err, 2);
	ft_putstr_fd("\n", 2);
}

void	error_ch(char *str)
{
	ft_putstr_fd("\033[34mminishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
	perror(" ");
	exit(1);
}
void	error_syntax(char *msg, char *caracter)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	if (ft_strcmp(caracter, ">") == 0 || ft_strcmp(caracter, ">>") == 0
		|| ft_strcmp(caracter, "<") == 0 || ft_strcmp(caracter, "<<") == 0)
	{
		ft_putstr_fd("`", 2);
		ft_putstr_fd(caracter, 2);
		ft_putstr_fd("'", 2);
	}
	else
		ft_putstr_fd(caracter, 2);
	ft_putstr_fd("\n", 2);
}

void	erro(char *str)
{
	ft_putstr_fd("\033[33mminishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
	perror(" ");
}

void	filecommade(t_cmd *cmd, char **env)
{
	struct stat	file_info;

	if (!cmd)
		exit(1);
	else if (cmd->single > 0 || cmd->double_q > 0)
	{
		ft_putstr_fd("\033[1;31msyntax error : error in quot\033[0m\n", 2);
		exit(1);
	}
	else if (cmd->option && cmd->option[0] && cmd->option[0][0] == '\0')
		errer_cmd(cmd->option[0], "command not found");
	else if (cmd->option[0] && cmd->option[0] && cmd->option[0][0] == '/')
	{
		if (access(cmd->option[0], F_OK))
		{
			errer_cmd(cmd->option[0], "No such file or directory");
			exit(127);
		}
		stat(cmd->option[0], &file_info);
		if (S_ISDIR(file_info.st_mode))
		{
			errer_cmd(cmd->option[0], "is a directory");
			exit(126);
		}
	}
	else if (cmd->option[0] && cmd->option[0] && cmd->option[0][0] == '.'
		&& cmd->option[0][1] == '/')
	{
		if (access(cmd->option[0], F_OK))
		{
			errer_cmd(cmd->option[0], "No such file or directory");
			exit(127);
		}
		if (access(cmd->option[0], X_OK) || access(cmd->option[0], R_OK)
			|| access(cmd->option[0], W_OK))
		{
			errer_cmd(cmd->option[0], "Permission denied");
			exit(126);
		}
		stat(cmd->option[0], &file_info);
		if (S_ISDIR(file_info.st_mode))
		{
			errer_cmd(cmd->option[0], "is a directory");
			exit(126);
		}
	}
	else if (cmd->option[0] && !get_path(env, cmd->option[0], 0))
	{
		errer_cmd(cmd->option[0], "command not found");
		exit(127);
	}
}

void	hand_error(t_status **status, char *str)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": error\n", 2);
	(*status)->status = 1;
}
void	free_string_array(char **array)
{
	int i ;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
