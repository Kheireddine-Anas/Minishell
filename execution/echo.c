/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:46:23 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/26 12:44:20 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_s(char **args, int *i)
{
	while (args[*i])
	{
		printf("%s", args[*i]);
		if (args[*i + 1]) 
			printf(" ");
		(*i)++;
	}
}

void	cmd_echo(char **args, t_status **status, t_cmd *cmd)
{
	int	i;
	int	newline;

	if (cmd->single > 0 || cmd->double_q > 0)
	{
		ft_putstr_fd("\033[34minishell: syntax error : error in quot\033[0m\n", 2);
		(*status)->status = 1;
		return ;
	}
	i = 1;
	newline = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	print_s(args, &i);
	if (newline)
		printf("\n");
	(*status)->status = 0;
}

int	cmd_exit(char **optin, t_status **status)
{
	int i;

	i = 0;
	if (optin[1])
	{
		while (optin[1][i])
		{
			if (!ft_isdigit(optin[1][i]))
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(optin[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit(255);
			}
			i++;
		}
		if (optin[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			(*status)->status = 1;
			return (1);
		}
		exit(ft_atoi(optin[1]));
	}
	exit(0);
	return (0);
}
