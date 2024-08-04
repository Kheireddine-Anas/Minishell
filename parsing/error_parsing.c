/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:35:05 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 16:06:37 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	condition_(t_Token *tokens, t_status **status, int num_tokens,
		int i)
{
	if ((tokens[i].type == IN || tokens[i].type == OUT
			|| tokens[i].type == APPEND || tokens[i].type == HER_DOC)
		&& (i < num_tokens && (tokens[i + 1].type == IN || tokens[i
					+ 1].type == OUT || tokens[i + 1].type == APPEND || tokens[i
					+ 1].type == HER_DOC)))
	{
		(*status)->status = 2;
		error_syntax("syntax error near unexpected token ", tokens[i
			+ 1].value);
		return (1);
	}
	else if ((tokens[i].type == IN || tokens[i].type == OUT
			|| tokens[i].type == APPEND || tokens[i].type == HER_DOC) && i
		+ 1 == num_tokens)
	{
		(*status)->status = 2;
		error_syntax("syntax error near unexpected token ", "`newline'");
		return (1);
	}
	return (0);
}

static int	condition2(t_Token *tokens, t_status **status, int num_tokens,
		int i)
{
	if (i == (num_tokens - 1) && tokens[i].type == PIP)
	{
		(*status)->status = 2;
		error_syntax("syntax error near unexpected token ", "`|'");
		return (1);
	}
	else if ((i == 0 && tokens[i].type == PIP) || (i != 0
			&& tokens[i].type == PIP && (tokens[i - 1].type == IN || tokens[i
					- 1].type == OUT || tokens[i - 1].type == APPEND || tokens[i
					- 1].type == HER_DOC)) || (tokens[i].type == PIP
			&& i < num_tokens && tokens[i + 1].type == PIP))
	{
		(*status)->status = 2;
		error_syntax("syntax error near unexpected token ", "`|'");
		return (1);
	}
	else if (condition_(tokens, status, num_tokens, i) == 1)
		return (1);
	return (0);
}

static void	printf_error_quut(t_status **status)
{
	(*status)->status = 2;
	ft_putstr_fd("\033[34minishell: ", 2);
	ft_putstr_fd("syntax error : error in quot\033[0m\n", 2);
}

int	chek_syntax_error(t_Token *tokens, t_status **status, int num_tokens)
{
	int	i;

	i = 0;
	while (i < num_tokens)
	{
		if (tokens[i].type == QUOTE_SINGLE && ft_strchr(tokens[i].value,
				'\'') != NULL)
		{
			printf_error_quut(status);
			return (1);
		}
		else if (tokens[i].type == QUOTE_DOUBLE && ft_strchr(tokens[i].value,
				'\"') != NULL)
		{
			printf_error_quut(status);
			return (1);
		}
		else if (condition2(tokens, status, num_tokens, i) == 1)
			return (1);
		i++;
	}
	return (0);
}
