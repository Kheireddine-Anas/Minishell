/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:57:46 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/03 13:06:43 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_cmd **cmd)
{
	if (cmd == NULL || *cmd == NULL)
		return ;
	if ((*cmd)->option && (*cmd)->option[0])
		free_string_array((*cmd)->option);
	else if (!(*cmd)->option[0])
		free((*cmd)->option);
	if ((*cmd)->extra_arg && (*cmd)->extra_arg[0])
		free_string_array((*cmd)->extra_arg);
	else if (!(*cmd)->extra_arg[0])
		free((*cmd)->extra_arg);
	if ((*cmd)->fil_name && (*cmd)->fil_name[0])
		free_string_array((*cmd)->fil_name);
	else if (!(*cmd)->fil_name[0])
		free((*cmd)->fil_name);
	if ((*cmd)->rederaction  && (*cmd)->rederaction[0])
		free_string_array((*cmd)->rederaction);
	else if (!(*cmd)->rederaction[0])
		free((*cmd)->rederaction);
}

void	lstclear(t_cmd **lst)
{
	t_cmd	*help;
	t_cmd	*next;

	if (!*lst)
		return ;
	help = *lst;
	while (help)
	{
		next = help->next;
		free_cmd(&help);
		free(help);
		help = next;
	}
	free(help);
	*lst = NULL;
}

int	lstsize(t_cmd *lst)
{
	t_cmd	*help;
	int		len;

	len = 0;
	help = lst;
	while (help != NULL)
	{
		help = help->next;
		len++;
	}
	return (len);
}

t_cmd	*lstlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

static void	add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (!*lst)
		*lst = new;
	else
	{
		last = lstlast(*lst);
		if (!last)
			return ;
		last->next = new;
	}
}

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
}

int	add_to_noud(t_Token *tokens, int *i, t_cmd **new, int num_tokens)
{
	int		j;
	int		k;
	int		m;
	int		l;
	int		capacite;
	char	**whilcart;
	int		h;

	h = 0;
	capacite = 3;
	j = 0;
	k = 0;
	l = 0;
	m = 0;
	whilcart = NULL;
	initialise_noud(new, capacite);
	while (*i < num_tokens && tokens)
	{
		if (tokens[*i].type == PIP)
		{
			free_string_array(whilcart);
			(*new)->extra_arg[m] = NULL;
			(*new)->rederaction[l] = NULL;
			(*new)->option[j] = NULL;
			(*new)->fil_name[k] = NULL;
			(*new)->next = NULL;
			return (1);
		}
		else if (tokens[*i].type == QUOTE_SINGLE && ft_strchr(tokens[*i].value,
				'\'') != NULL)
			(*new)->single = 1;
		else if (tokens[*i].type == QUOTE_DOUBLE && ft_strchr(tokens[*i].value,
				'\"') != NULL)
			(*new)->double_q = 1;
		else if (tokens[*i].type == IN || tokens[*i].type == HER_DOC
			|| tokens[*i].type == OUT || tokens[*i].type == APPEND)
		{
			if (l == st_2derra((*new)->rederaction, l))
			{
				(*new)->rederaction = realloc_array(&((*new)->rederaction),
						st_2derra((*new)->rederaction, l));
				if (!(*new)->rederaction)
					error_alocation();
			}
			(*new)->rederaction[l] = ft_strdup(tokens[*i].value);
			l++;
		}
		else if (tokens[*i].type == OPTION || tokens[*i].type == VARIABLE
			|| tokens[*i].type == QUOTE_SINGLE
			|| tokens[*i].type == QUOTE_DOUBLE || tokens[*i].type == WORD
			|| tokens[*i].type == CMD || tokens[*i].type == WHILCART)
		{
			if (j >= st_2derra((*new)->option, j))
			{
				(*new)->option = realloc_array(&((*new)->option),
						st_2derra((*new)->option, j));
				if (!(*new)->option)
					error_alocation();
			}
			if (tokens[*i].type == WHILCART)
			{
				tokens[*i].value = remouve_single_double_qout(tokens[*i].value);
				tokens[*i].value = sqipt_whil_cart(tokens[*i].value);
				whilcart = exe_wildcard(tokens[*i].value);
				if (!whilcart[0])
				{
					free(whilcart);
					whilcart = ft_calloc(2, sizeof(char *));
					whilcart[0] = ft_strdup(tokens[*i].value);
					whilcart[1] = NULL;
				}
				h = 0;
				while (whilcart[h])
				{
					if (j >= st_2derra((*new)->option, j))
					{
						(*new)->option = realloc_array(&((*new)->option),
								st_2derra((*new)->option, j));
						if (!(*new)->option)
							error_alocation();
					}
					(*new)->option[j] = ft_strdup(whilcart[h]);
					h++;
					j++;
				}
			}
			else
			{
				(*new)->option[j] = ft_strdup(tokens[*i].value);
				j++;
			}
		}
		else if (tokens[*i].type == FILE_IN || tokens[*i].type == FILE_OUT
			|| tokens[*i].type == LIM)
		{
			if (k >= st_2derra((*new)->fil_name, k))
			{
				(*new)->fil_name = realloc_array(&((*new)->fil_name),
						st_2derra((*new)->fil_name, k));
				if (!(*new)->fil_name)
					error_alocation();
			}
			(*new)->fil_name[k] = ft_strdup(tokens[*i].value);
			k++;
		}
		else
		{
			if (m >= st_2derra((*new)->extra_arg, m))
			{
				(*new)->extra_arg = realloc_array(&((*new)->extra_arg),
						st_2derra((*new)->extra_arg, m));
				if (!(*new)->extra_arg)
					error_alocation();
			}
			(*new)->extra_arg[m] = ft_strdup(tokens[*i].value);
			m++;
		}
		*i += 1;
	}
	free_string_array(whilcart);
	(*new)->extra_arg[m] = NULL;
	(*new)->rederaction[l] = NULL;
	(*new)->option[j] = NULL;
	(*new)->fil_name[k] = NULL;
	(*new)->next = NULL;
	return (0);
}
int	chek_syntax_error(t_Token *tokens, t_status **status, int num_tokens)
{
	int	i;

	i = 0;
	while (i < num_tokens)
	{
		if (tokens[i].type == QUOTE_SINGLE && ft_strchr(tokens[i].value,
				'\'') != NULL)
		{
			(*status)->status = 2;
			ft_putstr_fd("\033[34minishell: ", 2);
			ft_putstr_fd("syntax error : error in quot\033[0m\n", 2);
			return (1);
		}
		else if (tokens[i].type == QUOTE_DOUBLE && ft_strchr(tokens[i].value,
				'\"') != NULL)
		{
			(*status)->status = 2;
			ft_putstr_fd("\033[34minishell: ", 2);
			ft_putstr_fd("syntax error : error in quot\033[0m\n", 2);
			return (1);
		}
		else if (i == (num_tokens - 1) && tokens[i].type == PIP)
		{
			(*status)->status = 2;
			error_syntax("syntax error near unexpected token ", "`|'");
			return (1);
		}
		else if ((i == 0 && tokens[i].type == PIP) || (i != 0
				&& tokens[i].type == PIP && (tokens[i - 1].type == IN
					|| tokens[i - 1].type == OUT || tokens[i - 1].type == APPEND
					|| tokens[i - 1].type == HER_DOC)) || (tokens[i].type == PIP
				&& i < num_tokens && tokens[i + 1].type == PIP))
		{
			(*status)->status = 2;
			error_syntax("syntax error near unexpected token ", "`|'");
			return (1);
		}
		else if ((tokens[i].type == IN || tokens[i].type == OUT
				|| tokens[i].type == APPEND || tokens[i].type == HER_DOC)
			&& (i < num_tokens && (tokens[i + 1].type == IN || tokens[i
					+ 1].type == OUT || tokens[i + 1].type == APPEND || tokens[i
					+ 1].type == HER_DOC)))
		{
			(*status)->status = 2;
			error_syntax("syntax error near unexpected token ", tokens[i
				+ 1].value);
			return (1);
		}
		else if ((tokens[i].type == IN || tokens[i].type == OUT
				|| tokens[i].type == APPEND || tokens[i].type == HER_DOC) && i
			+ 1 == num_tokens)
		{
			(*status)->status = 2;
			error_syntax("syntax error near unexpected token ", "`newline'");
			return (1);
		}
		i++;
	}
	return (0);
}
void	creat_cmd(t_cmd **lst, char *command, char **env, t_status **status)
{
	int		i;
	t_cmd	*new;
	t_Token	*tokens;
	int		num_tokens;

	i = 0;
	num_tokens = 0;
	if (!command || ft_strlen(command) == 0)
		return ;
	tokens = tokenize(command, &num_tokens);
	parse(&tokens, num_tokens, env, status);
	if (!tokens)
		return ;
	if (chek_syntax_error(tokens, status, num_tokens) == 1)
	{
		i = 0;
		while (i < num_tokens)
		{
			free(tokens[i].value);
			i++;
		}
		free(tokens);
		return ;
	}
	while (i < num_tokens)
	{
		if (add_to_noud(tokens, &i, &new, num_tokens) == 1 && i < num_tokens)
		{
			if (new != NULL)
			{
				add_back(lst, new);
				new = NULL;
			}
			i++;
		}
		else
			add_back(lst, new);
	}
	i = 0;
	while (i < num_tokens)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
}
