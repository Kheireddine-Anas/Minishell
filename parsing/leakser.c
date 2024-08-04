/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leakser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:56:55 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 19:51:44 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_special_characters(char **p, t_Token **tokens, int *num_tokens,
		int *max_tokens)
{
	char	*start;
	int		len;

	if (*num_tokens >= *max_tokens)
		(*tokens) = realloc_cmd(tokens, max_tokens);
	if (!tokens)
		error_alocation();
	if (**p == '|')
	{
		(*tokens)[(*num_tokens)].type = PIP;
		(*tokens)[(*num_tokens)++].value = ft_strndup(*p, 1);
		(*p)++;
	}
	else if (**p == '*')
	{
		start = *p;
		while (**p != ' ' && **p != '\0')
			(*p)++;
		len = *p - start;
		(*tokens)[(*num_tokens)].type = WILDCARD;
		(*tokens)[(*num_tokens)++].value = ft_strndup(start, len);
	}
	else if (**p != '\0' && !is_space(**p) && **p != '<' && **p != '>')
		word(p, tokens, num_tokens);
}

t_Token	*tokenize(char *p, int *num_tokens)
{
	t_Token	*tokens;
	int		max_tokens;

	tokens = NULL;
	max_tokens = 2;
	*num_tokens = 0;
	tokens = ft_calloc(max_tokens, sizeof(t_Token));
	if (!tokens)
		error_alocation();
	while (*p)
	{
		condition(&p, &tokens, num_tokens, &max_tokens);
		process_special_characters(&p, &tokens, num_tokens, &max_tokens);
	}
	return (tokens);
}

void	condition(char **p, t_Token **tokens, int *num_tokens, int *max_tokens)
{
	if (*num_tokens >= *max_tokens)
	{
		(*tokens) = realloc_cmd(tokens, max_tokens);
		if (!tokens)
			error_alocation();
	}
	if (is_space(**p))
		(*p)++;
	else if (**p == '/' || **p == '.')
		quot(p, tokens, num_tokens, max_tokens);
	else if (**p == '<')
		in(p, tokens, num_tokens);
	else if (**p == '>')
		out(p, tokens, num_tokens);
	else if (is_space(**p))
	{
		while (**p && is_space(**p))
			(*p)++;
	}
}
