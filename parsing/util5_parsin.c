/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util5_parsin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:34:52 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/28 11:33:34 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*join_strings(char *s1, char *s2, char *s3, char *res)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		res[i++] = s2[j++];
	j = 0;
	while (s3[j] != '\0')
		res[i++] = s3[j++];
	res[i] = '\0';
	return (res);
}

char	*strjoi(char *s1, char *s2, char *s3)
{
	int		size_total;
	char	*res;

	if (!s1 || !s2 || !s3)
	{
		if (!s1)
			return (ft_strjoin(s2, s3));
		if (!s2)
			return (ft_strjoin(s1, s3));
		if (!s3)
			return (ft_strjoin(s1, s2));
	}
	size_total = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	res = ft_calloc(size_total, 1);
	if (!res)
		return (NULL);
	return (join_strings(s1, s2, s3, res));
}

void	condition(char **p, t_Token **tokens, int *num_tokens, int *max_tokens)
{
	char	*start;
	int		len;

	if (*num_tokens >= *max_tokens)
	{
		(*tokens) = realloc_cmd(tokens, max_tokens);
		if (!tokens)
			error_alocation();
	}
	if (is_space(**p))
		(*p)++;
	// else if ((**p == '\'' && *(*p + 1) == '\'' && *(*p + 2) != ' ')
	// 	|| (**p == '\"' && *(*p + 1) == '\"' && *(*p + 2) != ' '))
	// 	(*p) += 2;
	else if (**p == '/' || **p == '.'|| **p == '"'
		|| **p == '\'')
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
	else if (**p == '|')
	{
		(*tokens)[(*num_tokens)].type = PIP;
		(*tokens)[(*num_tokens)++].value = strndup(*p, 1);
		(*p)++;
	}
	else if (**p == '*')
	{
		start = *p;
		while (**p != ' ' && **p != '\0')
			(*p)++;
		len = *p - start;
		(*tokens)[(*num_tokens)].type = WHILCART;
		(*tokens)[(*num_tokens)++].value = strndup(start, len);
	}
	else if (**p != '\0'  && **p != '\"' && **p != '\''
		&& !is_space(**p) && **p != '<' && **p != '>')
		word(p, tokens, num_tokens);
}
