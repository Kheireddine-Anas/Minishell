/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3_add_tonoud.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:01:16 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 15:23:18 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	chek_error_while_card(t_Token *tokens, char **whilcart, int *i)
{
	if (!whilcart[0])
	{
		free(whilcart);
		whilcart = ft_calloc(2, sizeof(char *));
		whilcart[0] = ft_strdup(tokens[*i].value);
		whilcart[1] = NULL;
	}
}

void	handl_whil_card(t_cmd **new, int *i, char **whilcart, t_Token *tokens)
{
	int	h;

	h = 0;
	tokens[*i].value = remouve_single_double_qout(tokens[*i].value);
	tokens[*i].value = sqipt_whil_cart(tokens[*i].value);
	whilcart = exe_wildcard(tokens[*i].value);
	chek_error_while_card(tokens, whilcart, i);
	h = 0;
	while (whilcart[h])
	{
		if ((*new)->op >= st_2derra((*new)->option, (*new)->op))
		{
			(*new)->option = realloc_array(&((*new)->option),
					st_2derra((*new)->option, (*new)->op));
			if (!(*new)->option)
				error_alocation();
		}
		(*new)->option[(*new)->op] = ft_strdup(whilcart[h]);
		h++;
		(*new)->op += 1;
	}
	free_string_array(whilcart);
}

void	handl_option(int *i, t_Token *tokens, t_cmd **new)
{
	char	**whilcart;
	int		h;

	h = 0;
	whilcart = NULL;
	if (tokens[*i].type == OPTION || tokens[*i].type == VARIABLE
		|| tokens[*i].type == QUOTE_SINGLE || tokens[*i].type == QUOTE_DOUBLE
		|| tokens[*i].type == WORD || tokens[*i].type == CMD
		|| tokens[*i].type == WHILCART)
	{
		if ((*new)->op >= st_2derra((*new)->option, (*new)->op))
		{
			(*new)->option = realloc_array(&(*new)->option,
					st_2derra((*new)->option, (*new)->op));
			if (!(*new)->option)
				error_alocation();
		}
		if (tokens[*i].type == WHILCART)
			handl_whil_card(new, i, whilcart, tokens);
		else
		{
			(*new)->option[(*new)->op] = ft_strdup(tokens[*i].value);
			(*new)->op += 1;
		}
	}
}
