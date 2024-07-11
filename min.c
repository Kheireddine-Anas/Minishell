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

void	lex_init(t_lexer **lex, char *value, enum e_token type)
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

char	*word_type(char *input, int *i)
{
	char	*word;
	int		j;

	j = 0;
	while (input[*i + j] != '\'' && input[*i + j] != '\"' && input[*i + j] != '$' 
		&& input[*i + j] != '|' && input[*i + j] != '\0' && input[*i + j] != '<'
		&& input[*i + j] != '>' && input[*i + j] != ' ')
		j++;
	word = ft_calloc((j + 1), sizeof(char));
	j = 0;
	while (input[*i] != '\'' && input[*i] != '\"' && input[*i] != '$' 
		&& input[*i] != '|' && input[*i] != '\0' && input[*i] != '<'
		&& input[*i] != '>' && input[*i] != ' ')
		word[j++] = input[(*i)++];
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

lex_red(t_env **lexer, char *input, int *i)
{
	
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
			lex_init(&lexer, ft_strdup(&input[i]), S_QUOTE);
		else if (input[i] == '\"')
			lex_init(&lexer, ft_strdup(&input[i]), D_QUOTE);
		else if (input[i] == ' ')
				lex_init(&lexer, ft_strdup(" "), WSPACE);
		else if (input[i] == '|') //// pipe
			lex_init(&lexer, ft_strdup(&input[i]), PIPE);
		else if (input[i] == '$') /////dolar
			lex_init(&lexer, set_dollar(input, &i), VAR);
		else if (input[i] == '>' || input[i] == '<') /////Redirections
			lex_red(&lexer, input, &i);
		else
			lex_init(&lexer, word_type(input, &i), WORD);
		i++;
	}
	return (lexer);
}

int main()
{
	char	*input;
	t_lexer	*lexing;

	// signal(SIGINT, handle_sigint);
	// signal(SIGQUIT, SIG_IGN);
	lexing = NULL;
	while (1)
	{
		input = readline("Enter CMD: ");
		if (!input)
		{
			printf("\nCtrl+D pressed. Exiting...\n");
			break;
		}
		add_history(input);
		printf("CMD: %s\n", input);
		lexing = lex(lexing, input);
		ft_print_lexer(lexing);
		// pause();
		free(input);
	}
	return 0;
}
