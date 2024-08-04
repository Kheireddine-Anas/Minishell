/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3_add_tonoud.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:01:16 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 19:47:17 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	chek_error_while_card(t_Token *tokens, char **wildcards, int *i)
{
	if (!wildcards[0])
	{
		free(wildcards);
		wildcards = ft_calloc(2, sizeof(char *));
		wildcards[0] = ft_strdup(tokens[*i].value);
		wildcards[1] = NULL;
	}
}

void	handl_whil_card(t_cmd **new, int *i, char **wildcards, t_Token *tokens)
{
	int	h;

	h = 0;
	tokens[*i].value = remouve_single_double_qout(tokens[*i].value);
	tokens[*i].value = sqipt_whil_cart(tokens[*i].value);
	wildcards = exe_wildcard(tokens[*i].value);
	chek_error_while_card(tokens, wildcards, i);
	h = 0;
	while (wildcards[h])
	{
		if ((*new)->op >= st_2derra((*new)->option, (*new)->op))
		{
			(*new)->option = realloc_array(&((*new)->option),
					st_2derra((*new)->option, (*new)->op));
			if (!(*new)->option)
				error_alocation();
		}
		(*new)->option[(*new)->op] = ft_strdup(wildcards[h]);
		h++;
		(*new)->op += 1;
	}
	free_string_array(wildcards);
}

void	handl_option(int *i, t_Token *tokens, t_cmd **new)
{
	char	**wildcards;
	int		h;

	h = 0;
	wildcards = NULL;
	if (tokens[*i].type == OPTION || tokens[*i].type == VARIABLE
		|| tokens[*i].type == QUOTE_SINGLE || tokens[*i].type == QUOTE_DOUBLE
		|| tokens[*i].type == WORD || tokens[*i].type == CMD
		|| tokens[*i].type == WILDCARD)
	{
		if ((*new)->op >= st_2derra((*new)->option, (*new)->op))
		{
			(*new)->option = realloc_array(&(*new)->option,
					st_2derra((*new)->option, (*new)->op));
			if (!(*new)->option)
				error_alocation();
		}
		if (tokens[*i].type == WILDCARD)
			handl_whil_card(new, i, wildcards, tokens);
		else
		{
			(*new)->option[(*new)->op] = ft_strdup(tokens[*i].value);
			(*new)->op += 1;
		}
	}
}
