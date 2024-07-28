#include "minishell.h"


char	*get_status(t_status status)
{
	if (status == IN_DQUOTE)
		return ("IN_DQUOTE");
	else if (status == IN_SQUOTE)
		return ("IN_SQUOTE");
	else
		return ("GENERAL");
}

char	*get_type(t_token token)
{
	if (token == WSPACE)
		return ("SPACE");
	else if (token == S_QUOTE)
		return ("S_QUOTE");
	else if (token == D_QUOTE)
		return ("DOUBLE_QUOTE");
	else if (token == BACK_SL)
		return ("ESCAPE");
	else if (token == VAR)
		return ("VAR");
	else if (token == PIPE)
		return ("PIPE");
	else if (token == WORD)
		return ("WORD");
	else if (token == HERE_DOC)
		return ("HERE_DOC");
	else if (token == RE_OUT)
		return ("REDIR_OUT");
	else if (token == RE_IN)
		return ("REDIR_IN");
	else
		return ("ERROR");
}

void	ft_print_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	if (tmp)
	{
		printf("tmp->content\t");
		printf("tmp->type\t");
		printf("tmp->status\t\n");
		printf("------------------------------------------------\n");
	}
	while (tmp)
	{
		printf("%-10s\t", tmp->value);
		printf("%-10s\t", get_type(tmp->type));
		printf("%-10s\t\n", get_status(tmp->status));
		printf("------------------------------------------------\n");
		tmp = tmp->next;
	}
}

