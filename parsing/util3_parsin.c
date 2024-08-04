/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3_parsin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:17:59 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 19:14:03 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quot(char **p, t_Token **tokens, int *num_tokens, int *max_tokens)
{
	char	*start;
	int		len;
	char	c;

	if (*num_tokens >= *max_tokens)
	{
		*tokens = realloc_cmd(tokens, max_tokens);
		if (!tokens)
			error_alocation();
	}
	if (**p == '/' || **p == '.')
	{
		c = **p;
		start = (*p)++;
		while (**p != ' ' && **p && **p != '\"' && **p != '\'')
			(*p)++;
		len = *p - start;
		if (c == '/' || c == '.')
			(*tokens)[(*num_tokens)].type = CMD;
		else
			(*tokens)[(*num_tokens)].type = WORD;
		(*tokens)[(*num_tokens)++].value = ft_strndup(start, len);
	}
}

t_Token	*realloc_cmd(t_Token **tokens, int *capacity)
{
	int		i;
	t_Token	*new_cmd;

	*capacity *= 2;
	new_cmd = ft_calloc(*capacity, sizeof(t_Token));
	if (!new_cmd)
	{
		free(*tokens);
		return (NULL);
	}
	i = 0;
	while (i < *capacity / 2)
	{
		new_cmd[i].type = (*tokens)[i].type;
		new_cmd[i].value = ft_strdup((*tokens)[i].value);
		free((*tokens)[i].value);
		i++;
	}
	free(*tokens);
	return (new_cmd);
}

char	**realloc_array(char ***str, int capacity)
{
	int		i;
	char	**new_cmd;

	capacity += 2;
	new_cmd = ft_calloc(capacity, sizeof(char *));
	if (!new_cmd)
	{
		free(*str);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < (capacity - 2) && (*str)[i] != NULL)
	{
		new_cmd[i] = ft_strdup((*str)[i]);
		free((*str)[i]);
		i++;
	}
	free(*str);
	return (new_cmd);
}

char	**create_cmmmand(char **str)
{
	int		i;
	int		j;
	char	**result;

	j = 0;
	i = 0;
	while (str[i])
		i++;
	result = ft_calloc(i, sizeof(char *));
	if (!result)
		exit(EXIT_FAILURE);
	i = 0;
	while (str[i])
	{
		if (ft_strlen(str[i]) > 0)
		{
			result[j] = ft_strdup(str[i]);
			j++;
		}
		i++;
	}
	result[j] = NULL;
	free_string_array(str);
	return (result);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}
