/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:37:54 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/31 15:24:39 by ahamdi           ###   ########.fr       */
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
int	chke_sigl_double_quote(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		if (str[i] == '\"')
			return (2);
		i++;
	}
	return (0);
}
void	word(char **p, t_Token **tokens, int *num_tokens)
{
	char	*start;
	int		len;
	char	c;
	char	h;

	int in_single_quotes = 0;
	int in_double_quotes = 0;
	if (*num_tokens != 0)
		c = *(*p - 1);
	h = **p;
	start = *p;
	while (**p != '\0' && (in_single_quotes || in_double_quotes
			|| (!is_space(**p) && **p != '|' && **p != '<' && **p != '>')))
	{
		if (**p == '\'')
			in_single_quotes = !in_single_quotes;
		else if (**p == '\"')
			in_double_quotes = !in_double_quotes;
		(*p)++;
	}
	len = (*p) - start;
	(*tokens)[*num_tokens].value = strndup(start, len);
	if (h == '-' && (*tokens)[*num_tokens].value[1] != '\'' && (*tokens)[*num_tokens].value[1] != '\"')
		(*tokens)[(*num_tokens)].type = OPTION;
	else
	{
		if (chke_sigl_double_quote((*tokens)[*num_tokens].value) == 1)
			(*tokens)[(*num_tokens)].type = QUOTE_SINGLE;
		else if (chke_sigl_double_quote((*tokens)[*num_tokens].value) == 2)
			(*tokens)[(*num_tokens)].type = QUOTE_DOUBLE;
		else 
			(*tokens)[(*num_tokens)].type = WORD;
	}
	(*num_tokens)++;
}
