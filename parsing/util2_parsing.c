/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:37:54 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 19:13:32 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	out(char **p, t_Token **tokens, int *num_tokens)
{
	char	*start;
	int		len;

	start = (*p)++;
	if (**p == '>')
	{
		len = 2;
		(*tokens)[(*num_tokens)].type = APPEND;
		(*tokens)[(*num_tokens)++].value = ft_strndup(start, len);
		(*p)++;
	}
	else
	{
		len = 1;
		(*tokens)[(*num_tokens)].type = OUT;
		(*tokens)[(*num_tokens)++].value = ft_strndup(start, len);
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
		(*tokens)[(*num_tokens)++].value = ft_strndup(start, len);
		(*p)++;
	}
	else
	{
		len = 1;
		(*tokens)[(*num_tokens)].type = IN;
		(*tokens)[(*num_tokens)++].value = ft_strndup(start, len);
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

static void	condition_word(char h, t_Token **tokens, int *num_tokens)
{
	if (h == '-' && (*tokens)[*num_tokens].value[1] != '\''
		&& (*tokens)[*num_tokens].value[1] != '\"')
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
}

void	word(char **p, t_Token **tokens, int *num_tokens)
{
	char	*start;
	int		len;
	char	h;
	int		in_single_quotes;
	int		in_double_quotes;

	h = **p;
	in_single_quotes = 0;
	in_double_quotes = 0;
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
	(*tokens)[*num_tokens].value = ft_strndup(start, len);
	condition_word(h, tokens, num_tokens);
	(*num_tokens)++;
}
