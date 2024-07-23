/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eroor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:52:46 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/23 15:59:45 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_alocation(void)
{
	perror("Allocation error");
	exit(1);
}

void	errer_cmd(char *str)
{
	ft_putstr_fd("\033[31mminishell: ", 2); 
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
	ft_putstr_fd("\033[31m", 2); 
	perror(" ");
	ft_putstr_fd("\033[0m", 2);
	exit(127);
}

void	error_ch(char *str)
{
	ft_putstr_fd("\033[34mminishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
	ft_putstr_fd("\033[34m", 2);
	perror(" ");
	ft_putstr_fd("\033[0m", 2);
	exit (1);
}

void	erro(char *str)
{
	ft_putstr_fd("\033[33mminishell: ", 2); 
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\033[0m", 2);
	ft_putstr_fd("\033[33m", 2);
	perror(" ");
	ft_putstr_fd("\033[0m", 2);
}

void	filecommade(t_cmd *cmd, char **env)
{
	if (!cmd)
		exit (1);
	else if (cmd->single > 0 || cmd->double_q > 0)
	{
		ft_putstr_fd("\033[1;31msyntax error : error in quot\033[0m\n", 2);
		exit(1);
	}
	else if (cmd->option && cmd->option[0] && cmd->option[0][0] == '\0')
		errer_cmd(cmd->option[0]);
	else if (cmd->option[0] && cmd->option[0] && cmd->option[0][0] == '/')
	{
		if (access(cmd->option[0], X_OK) != 0)
			errer_cmd(cmd->option[0]);
	}
	else if (cmd->option[0] && cmd->option[0] 
		&& cmd->option[0][0] == '.' && cmd->option[0][1] == '/')
	{
		if (access(cmd->option[0], X_OK))
			errer_cmd(cmd->option[0]);
	}
	else if (cmd->option[0] && !get_path(env, cmd->option[0], 0))
		errer_cmd(cmd->option[0]);
}
void	hand_error(t_status **status, char	*str)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": error\n", 2);
	(*status)->status = 1;
}

// void	print_minishell(void)
// {
// 	char	*shell_art;

// 	shell_art = 
// 		"  _____ _          _ _ \n"
// 		" / ____| |        | | |\n"
// 		"| (___ | |__   ___| | |\n"
// 		" \\___ \\| '_ \\ / _ \\ | |\n"
// 		" ____) | | | |  __/ | |\n"
// 		"|_____/|_| |_|\\___|_|_|\n";
// 	ft_putstr_fd("\033[34m", 2);
// 	ft_putstr_fd(shell_art, 2);
// 	ft_putstr_fd("\033[0m", 2);
// }
