/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:34:41 by akheired          #+#    #+#             */
/*   Updated: 2024/07/26 18:34:41 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void handle_sigint(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		printf("\n");
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

void	lex_init(t_lexer **lex, char *value, t_token type)
{
	t_lexer	*new;
	t_lexer	*tmp;

	tmp = *lex;
	new = ft_calloc(1, sizeof(t_lexer));
	new->value = value;
	new->type = type;
	new->next = NULL;
	if (!tmp)
	{
		*lex = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

char	*word_type(char *inpt, int *i)
{
	char	*word;
	int		j;

	j = 0;
	while (inpt[*i + j] != '\'' && inpt[*i + j] != '\"' && inpt[*i + j] != '$'
		&& inpt[*i + j] != '|' && inpt[*i + j] != '\0' && inpt[*i + j] != '<'
		&& inpt[*i + j] != '>' && inpt[*i + j] != ' ')
		j++;
	word = ft_calloc((j + 1), sizeof(char));
	j = 0;
	while (inpt[*i] != '\'' && inpt[*i] != '\"' && inpt[*i] != '$' 
		&& inpt[*i] != '|' && inpt[*i] != '\0' && inpt[*i] != '<'
		&& inpt[*i] != '>' && inpt[*i] != ' ')
		word[j++] = inpt[(*i)++];
	word[j] = '\0';
	(*i)--;
	return (word);
}

char	*dollar_name(char *name, int *i)
{
	int		j;
	char	*str;

	j = 0;
	while (ft_isalnum(name[*i + j]) || name[*i + j] == '_')
		j++;
	str = ft_calloc(j + 2, sizeof(char));
	j = 0;
	str[j++] = '$';
	while (ft_isalnum(name[*i]) || name[*i] == '_')
		str[j++] = name[(*i)++];
	str[j] = '\0';
	(*i)--;
	return (str);
}

char	*set_dollar(char *name, int *i)
{
	char	value[5];

	while (name[*i])
	{
		(*i)++;
		if (name[*(i)] == '$')
			return (ft_strdup("$$"));
		else if (name[*(i)] == '?')
			return (ft_strdup("$?"));
		else if (name[*(i)] == '@')
			return (ft_strdup(""));
		else if (ft_isalpha(name[*(i)]) || name[(*i) == '_'])
			return (dollar_name(name, i));
		else if (ft_isdigit(name[*(i)]))
		{
			value[0] = '$';
			value[1] = name[*i];
			value[2] = '\0';
		}
		else
		{
			(*i)--;
			return (ft_strdup("$"));
		}
	}
	return (ft_strdup("$"));
}

void	lex_red(t_lexer **lexer, char *input, int *i)
{
	if (input[*i] == '>' && input[*i + 1] && input[*i + 1] == '>')
	{
		(*i)++;
		lex_init(lexer, ft_strdup(">>"), RE_OUT);
	}
	else if (input[*i] == '<' && input[*i + 1] && input[*i + 1] == '<')
	{
		(*i)++;
		lex_init(lexer, ft_strdup("<<"), HERE_DOC);
	}
	else if (input[*i] == '>')
		lex_init(lexer, ft_strdup(">"), RE_OUT);
	else if (input[*i] == '<')
		lex_init(lexer, ft_strdup("<"), RE_IN);
}

t_lexer	*s_qoutes(t_lexer	*lex)
{
	lex = lex->next;
	while (lex && lex->next && lex->type != S_QUOTE)
	{
		lex->status = IN_SQUOTE;
		lex->type = WORD;
		lex = lex->next;
	}
	return (lex);
}

t_lexer	*d_qoutes(t_lexer *lex)
{
	lex = lex->next;
	while (lex && lex->next && lex->type != D_QUOTE)
	{
		lex->status = IN_DQUOTE;
		if (lex->type != VAR)
			lex->type = WORD;
		lex = lex->next;
	}
	return (lex);
}

void	check_quotes(t_lexer **lexer)
{
	t_lexer	*lex_tmp;

	lex_tmp = *lexer;
	while (lex_tmp && lex_tmp->next)
	{
		if (lex_tmp->type == S_QUOTE)
			lex_tmp = s_qoutes(lex_tmp);
		else if (lex_tmp->type == D_QUOTE)
			lex_tmp = d_qoutes(lex_tmp);
		else
			lex_tmp->status = GENERAL;
		lex_tmp = lex_tmp->next;
	}
}

t_lexer	*lex(t_lexer *lexer, char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (!input[i])
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\'')
			lex_init(&lexer, ft_strdup("\'"), S_QUOTE);
		else if (input[i] == '\"')
			lex_init(&lexer, ft_strdup("\""), D_QUOTE);
		else if (input[i] == ' ')
			lex_init(&lexer, ft_strdup(" "), WSPACE);
		else if (input[i] == '|')
			lex_init(&lexer, ft_strdup("|"), PIPE);
		else if (input[i] == '$')
			lex_init(&lexer, set_dollar(input, &i), VAR);
		else if (input[i] == '>' || input[i] == '<')
			lex_red(&lexer, input, &i);
		else
			lex_init(&lexer, word_type(input, &i), WORD);
		i++;
	}
	check_quotes(&lexer);
	return (lexer);
}

t_env	*obtain_env(char **envis)
{
	int		i;
	t_env	*env;
	t_env	*tmp;

	i = 0;
	env = set_env(envis[i++]);
	tmp = env;
	while (envis[i])
	{
		tmp->next = set_env(envis[i]);
		tmp = tmp->next;
		i++;
	}
	return (env);
}

void	vars_value(t_lexer *tmp)
{
	free(tmp->value);
	tmp->value = ft_strdup("$");
	tmp->type = WORD;
}

char	*find_var(t_env *env, char *var_name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(var_name, tmp->variable))
		{
			free(var_name);
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	free(var_name);
	return ("");
}

void	vars_status(t_env *env, t_lexer *tmp)
{
	char	*var_name;

	var_name = ft_strdup(tmp->value + 1);
	free(tmp->value);
	tmp->value = ft_strdup(find_var(env, var_name));
	tmp->type = WORD;
}

void	anothers(t_env *env, t_lexer *lex)
{
	char	*var_name;

	var_name = ft_strdup(lex->value + 1);
	free(lex->value);
	lex->value = ft_strdup(find_var(env, var_name));
	lex->value = strtrim_mine(lex->value, '\t');
	lex->value = strtrim_mine(lex->value, ' ');
	lex->type = WORD;
}
void	var_extend(t_lexer **lexing, t_env *env)
{
	t_lexer	*tmp;

	tmp = *lexing;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			if (!ft_strcmp(tmp->value, "$"))
				vars_value(tmp);
			else if (tmp->value[0] == '\0')
				tmp->type = WORD;
			else if (!ft_strcmp(tmp->value, "$?"))
			{
				free(tmp->value);
				tmp->value = ft_itoa(g_exit.exit_status);
				tmp->type = WORD;
			}
			else if (tmp->status == IN_DQUOTE)
				vars_status(env, *lexing);
			else
				anothers(env, tmp);
		}
		tmp = tmp->next;
	}
}

t_lexer	*del_nd(t_lexer *lexer, t_lexer *node)
{
	t_lexer	*next_node;
	t_lexer	*tmp;

	if (lexer == node)
	{
		next_node = lexer->next;
		free(lexer->value);
		free(lexer);
		lexer = NULL;
		return (next_node);
	}
	tmp = lexer;
	while (tmp && tmp->next != node)
		tmp = tmp->next;
	next_node = NULL;
	if (tmp)
	{
		if (tmp->next->next)
			next_node = tmp->next->next;
		free(tmp->next->value);
		free(tmp->next);
		tmp->next = next_node;
	}
	return (lexer);
}

t_lexer	*interm(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (tmp && tmp->next)
	{
		if ((tmp->type == WORD && tmp->status == GENERAL)
			&& (tmp->next->type == WORD && tmp->next->status == GENERAL))
		{
			tmp->value = ft_strjoin(tmp->value, tmp->next->value);
			lexer = del_nd(lexer, tmp->next);
			tmp = lexer;
		}
		else if ((tmp->type == WORD && tmp->status == IN_DQUOTE)
			&& (tmp->next->type == WORD && tmp->next->status == IN_DQUOTE))
		{
			tmp->value = ft_strjoin(tmp->value, tmp->next->value);
			lexer = del_nd(lexer, tmp->next);
			tmp = lexer;
		}
		tmp = tmp->next;
	}
	return (lexer);
}

void	quotes_rm(t_lexer **lexer)
{
	t_lexer	*tmp;
	t_lexer	*tmps;

	tmp = *lexer;
	while (tmp)
	{
		tmps = tmp->next;
		if (tmp->type == S_QUOTE || tmp->type == D_QUOTE)
			*lexer = del_nd(*lexer, tmp);
		tmp = tmps;
	}
	interm(*lexer);
}

t_lexer	*rm_space(t_lexer *lexer)
{
	t_lexer	*tmp;
	t_lexer	*prvs;
	t_lexer	*elem_rm;

	tmp = lexer;
	prvs = NULL;
	while (tmp)
	{
		if (tmp->type == WSPACE)
		{
			elem_rm = tmp;
			tmp = tmp->next;
			if (prvs)
				prvs->next = tmp;
			else
				lexer = tmp;
			free(elem_rm->value);
			free(elem_rm);
		}
		else
			tmp = ((prvs = tmp), tmp->next);
	}
	return (lexer);
}

void	lexer_free(t_lexer *lexer)
{
	t_lexer	*tmp;

	while (lexer)
	{
		tmp = lexer;
		lexer = lexer->next;
		free(tmp->value);
		free(tmp);
	}
}

int	check_redir(t_lexer *lexing)
{
	t_lexer	*tmp;

	tmp = lexing;
	if (tmp->type == RE_OUT || tmp->type == RE_IN
		|| tmp->type == HERE_DOC || tmp->type == OUT_FILE)
		return (0);
	return (1);
}

t_lexer	*org_pipe(t_lexer *lexing)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = lexing;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (!tmp->next || i == 0 || (tmp->next->type != WORD
					&& check_redir(tmp->next)))
			{
				printf("syntax error PIPE\n");
				lexer_free(lexing);
				return (NULL);
			}
		}
		i++;
		tmp = tmp->next;
	}
	return (lexing);
}

void	org_cmd(t_lexer **lexing)
{
	t_lexer	*tmp;

	*lexing = org_pipe(*lexing);
	tmp = *lexing;
	while (tmp)
	{
		if (tmp->type == RE_OUT || tmp->type == RE_IN
			|| tmp->type == HERE_DOC || tmp->type == OUT_FILE)
		{
			if (!tmp->next || (tmp->next->type != VAR
					&& tmp->next->type != WORD))
			{
				printf("parse error REdir\n");
				lexer_free(*lexing);
				*lexing = NULL;
			}
		}
		tmp = tmp->next;
	}
	if (!(*lexing))
		g_exit.exit_status = 2;
}

void	lex_scan(t_lexer **lexing, t_env *env)
{
	t_lexer	*tmp;

	var_extend(lexing, env);
	quotes_rm(lexing);
	tmp = *lexing;
	while (tmp && tmp->next)
	{
		if ((tmp->type == VAR && tmp->next->type == WORD)
			|| (tmp->status == IN_SQUOTE && tmp->next->status == IN_SQUOTE)
			|| (tmp->status == IN_DQUOTE && tmp->type != VAR
				&& tmp->next->type != VAR && tmp->next->status == IN_DQUOTE)
			|| (tmp->type == WORD && tmp->next->type == WORD))
		{
			tmp->value = ft_strjoin(tmp->value, tmp->next->value);
			*lexing = del_nd(*lexing, tmp->next);
		}
		else
			tmp = tmp->next;
	}
	*lexing = rm_space(*lexing);
	org_cmd(lexing);
}

int main(int ac, char **av, char **environment)
{
	char	*input;
	t_lexer	*lexing;
	t_env	*env;

	// signal(SIGINT, handle_sigint);
	// signal(SIGQUIT, SIG_IGN);
	lexing = NULL;
	env = obtain_env(environment);
	(void)ac;
	(void)av;
	while (1)
	{
		input = readline("Enter CMD: ");
		if (!input)
		{
			printf("\nCtrl+D pressed. Exiting...\n");
			break ;
		}
		add_history(input);
		// printf("CMD: %s\n", input);
		lexing = lex(lexing, input);
		lex_scan(&lexing, env);
		ft_print_lexer(lexing);
		// printf("..........................................................\n");
		// pause();
		free(input);
		break;
	}
	printf("Exit: %d\n", g_exit.exit_status);
	// while (env) //Uncomment this loop to see ENV struct
	// {
	// 	printf("%s=%s\n", env->variable, env->value);
	// 	env = env->next;
	// }
	return 0;
}
