/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:46:23 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/26 09:18:43 by ahamdi           ###   ########.fr       */
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
