/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2_add_to_neoud.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:01:22 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 19:07:06 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handl_rediraction(int *i, t_Token *tokens, t_cmd **new)
{
	if ((*new)->re == st_2derra((*new)->rederaction, (*new)->re))
	{
		(*new)->rederaction = realloc_array(&((*new)->rederaction),
				st_2derra((*new)->rederaction, (*new)->re));
		if (!(*new)->rederaction)
			error_alocation();
	}
	(*new)->rederaction[(*new)->re] = ft_strdup(tokens[*i].value);
	(*new)->re += 1;
}

void	handfile_name(int *i, t_Token *tokens, t_cmd **new)
{
	if ((*new)->fi >= st_2derra((*new)->fil_name, (*new)->fi))
	{
		(*new)->fil_name = realloc_array(&((*new)->fil_name),
				st_2derra((*new)->fil_name, (*new)->fi));
		if (!(*new)->fil_name)
			error_alocation();
	}
	(*new)->fil_name[(*new)->fi] = ft_strdup(tokens[*i].value);
	(*new)->fi += 1;
}

void	hand_type(int *i, t_Token *tokens, t_cmd **new)
{
	if (tokens[*i].type == OPTION || tokens[*i].type == VARIABLE
		|| tokens[*i].type == QUOTE_SINGLE || tokens[*i].type == QUOTE_DOUBLE
		|| tokens[*i].type == WORD || tokens[*i].type == CMD
		|| tokens[*i].type == WHILCART)
		handl_option(i, tokens, new);
	else if (tokens[*i].type == IN || tokens[*i].type == HER_DOC
		|| tokens[*i].type == OUT || tokens[*i].type == APPEND)
		handl_rediraction(i, tokens, new);
	else if (tokens[*i].type == FILE_IN || tokens[*i].type == FILE_OUT
		|| tokens[*i].type == LIM)
		handfile_name(i, tokens, new);
	else
	{
		if ((*new)->ex >= st_2derra((*new)->extra_arg, (*new)->ex))
		{
			(*new)->extra_arg = realloc_array(&((*new)->extra_arg),
					st_2derra((*new)->extra_arg, (*new)->ex));
			if (!(*new)->extra_arg)
				error_alocation();
		}
		(*new)->extra_arg[(*new)->ex] = ft_strdup(tokens[*i].value);
		(*new)->ex += 1;
	}
}

static void	fin_initilat(t_cmd **new)
{
	(*new)->extra_arg[(*new)->ex] = NULL;
	(*new)->rederaction[(*new)->re] = NULL;
	(*new)->option[(*new)->op] = NULL;
	(*new)->fil_name[(*new)->fi] = NULL;
	(*new)->next = NULL;
}

int	add_to_noud(t_Token *tokens, int *i, t_cmd **new, int num_tokens)
{
	initialise_noud(new, 3);
	while (*i < num_tokens && tokens)
	{
		if (tokens[*i].type == PIP)
		{
			fin_initilat(new);
			return (1);
		}
		else if (tokens[*i].type == QUOTE_SINGLE && ft_strchr(tokens[*i].value,
				'\'') != NULL)
			(*new)->single = 1;
		else if (tokens[*i].type == QUOTE_DOUBLE && ft_strchr(tokens[*i].value,
				'\"') != NULL)
			(*new)->double_q = 1;
		hand_type(i, tokens, new);
		*i += 1;
	}
	fin_initilat(new);
	return (0);
}
