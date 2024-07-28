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

// var_extend(t_lexer **lexing, t_env *env)
// {
// 	t_lexer	*tmp;

// 	tmp = *lexing;
// 	while (tmp)
// 	{
// 		if (tmp->type == VAR)
// 		{

// 		}
// 	}
	
// }

// lex_scan(t_lexer **lexing, t_env *env)
// {
// 	var_extend(lexing, env);
// }

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
		// lex_scan(lexing, env);
		ft_print_lexer(lexing);
		// printf("..........................................................\n");
		// pause();
		free(input);
		break;
	}
	// while (env) //Uncomment this loop to see ENV struct
	// {
	// 	printf("%s=%s\n", env->variable, env->value);
	// 	env = env->next;
	// }
	return 0;
}
