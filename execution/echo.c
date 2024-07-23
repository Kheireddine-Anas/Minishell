/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:46:23 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/20 14:46:55 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_echo(char **args, t_status **status, t_cmd *cmd)
{
	int	i;
	int	newline;

	if (cmd->single > 0 || cmd->double_q > 0)
	{
		ft_putstr_fd("\033[34minishell: ", 2);
		ft_putstr_fd("syntax error : error in quot\033[0m\n", 2);
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
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1]) 
		{
			printf(" ");
		}
		i++;
	}
	if (newline)
		printf("\n");
	(*status)->status = 0;
}
