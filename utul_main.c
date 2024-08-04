/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utul_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:48:54 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 16:56:42 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chke_arg(int argc)
{
	if (argc != 1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(127);
	}
}

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

int	chek_builting(t_cmd *lst_cmd, t_env **env, t_status **status,
		t_fd_ **fd_in_out)
{
	if (builting(lst_cmd, env, status, fd_in_out) == 1)
	{
		dup2((*fd_in_out)->fd_in, STDIN_FILENO);
		dup2((*fd_in_out)->fd_out, STDOUT_FILENO);
		close_file(*fd_in_out, (*fd_in_out)->fd);
		free_string_array((*fd_in_out)->envp);
		free(*fd_in_out);
		lstclear(&lst_cmd);
		return (1);
	}
	return (0);
}
