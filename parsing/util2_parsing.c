/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:37:54 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/20 13:18:54 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

void	out(char **p, t_Token **tokens, int *num_tokens)
{
	char	*start;
	int		len;

	start = (*p)++;
	if (**p == '>')
	{
		len = 2;
		(*tokens)[(*num_tokens)].type = APPEND;
		(*tokens)[(*num_tokens)++].value = strndup(start, len);
		(*p)++;
	}
	else
	{
		len = 1;
		(*tokens)[(*num_tokens)].type = OUT;
		(*tokens)[(*num_tokens)++].value = strndup(start, len);
	}
}

void	in(char **p, t_Token **tokens, int *num_tokens)
{
	char	*start;
	int		len;

	start = (*p)++;
	if (**p == '<')
	{
		len = 2;
		(*tokens)[(*num_tokens)].type = HER_DOC;
		(*tokens)[(*num_tokens)++].value = strndup(start, len);
		(*p)++;
	}
	else
	{
		len = 1;
		(*tokens)[(*num_tokens)].type = IN;
		(*tokens)[(*num_tokens)++].value = strndup(start, len);
	}
}

void	word(char **p, t_Token **tokens, int *num_tokens)
{
	char	*start;
	int		len;
	char	c;
	char	h;

	if (*num_tokens != 0)
		c = *(*p - 1);
	h = **p;
	start = *p;
	while (**p != '\0' && **p != '$' && **p != '\"' && **p != '\''
		&& !is_space(**p) && **p != '|' && **p != '<' && **p != '>')
		(*p)++;
	len = (*p) - start;
	if (h == '-')
		(*tokens)[(*num_tokens)].type = OPTION;
	else
		(*tokens)[(*num_tokens)].type = WORD;
	(*tokens)[(*num_tokens)++].value = strndup(start, len);
}
