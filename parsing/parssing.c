/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:57:46 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 19:07:39 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialise_noud(t_cmd **new, int cp)
{
	*new = ft_calloc(1, sizeof(t_cmd));
	if (!*new)
		error_alocation();
	(*new)->single = 0;
	(*new)->double_q = 0;
	(*new)->option = ft_calloc(cp, sizeof(char *));
	if (!(*new)->option)
		error_alocation();
	(*new)->extra_arg = ft_calloc(cp, sizeof(char *));
	if (!(*new)->extra_arg)
		error_alocation();
	(*new)->rederaction = ft_calloc(cp, sizeof(char *));
	if (!(*new)->rederaction)
		error_alocation();
	(*new)->fil_name = ft_calloc(cp, sizeof(char *));
	if (!(*new)->fil_name)
		error_alocation();
	(*new)->op = 0;
	(*new)->re = 0;
	(*new)->fi = 0;
	(*new)->ex = 0;
}

static int	chek_syntax(t_Token **tokens, t_status **status, int num_tokens)
{
	int	i;

	i = 0;
	if (chek_syntax_error(*tokens, status, num_tokens) == 1)
	{
		while (i < num_tokens)
		{
			free((*tokens)[i].value);
			i++;
		}
		free(*tokens);
		return (1);
	}
	return (0);
}

static int	loop_creat_cmd(t_Token **tokens, t_status **status, int num_tokens,
		t_cmd **lst)
{
	t_cmd	*new;
	int		i;

	i = 0;
	new = NULL;
	if (chek_syntax(tokens, status, num_tokens) == 1)
		return (1);
	while (i < num_tokens)
	{
		if (add_to_noud(*tokens, &i, &new, num_tokens) == 1 && i < num_tokens)
		{
			if (new)
			{
				add_back_principal(lst, new);
				new = NULL;
			}
			i++;
		}
		else
			add_back_principal(lst, new);
	}
	return (0);
}

t_cmd	*creat_cmd(t_cmd **lst, char *command, char **env, t_status **status)
{
	int		i;
	t_Token	*tokens;
	int		num_tokens;

	i = 0;
	num_tokens = 0;
	if (!command || ft_strlen(command) == 0)
		return (NULL);
	tokens = tokenize(command, &num_tokens);
	parse(&tokens, num_tokens, env, status);
	if (!tokens)
		return (NULL);
	if (loop_creat_cmd(&tokens, status, num_tokens, lst) == 1)
		return (NULL);
	i = 0;
	while (i < num_tokens)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
	return (*lst);
}

int	st_2derra(char **str, int k)
{
	int	i;

	if (!k)
		return (0);
	str[k] = NULL;
	i = 0;
	while (str[i])
		i++;
	return (i);
}
