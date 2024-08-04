/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eroor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:52:46 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/03 15:18:54 by ahamdi           ###   ########.fr       */
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
