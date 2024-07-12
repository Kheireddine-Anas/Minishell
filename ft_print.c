#include "minishell.h"


// char	*get_state(enum e_state state)
// {
// 	if (state == IN_DQUOTE)
// 		return ("IN_DQUOTE");
// 	else if (state == IN_QUOTE)
// 		return ("IN_QUOTE");
// 	else
// 		return ("GENERAL");
// }

char	*get_type(e_token token)
{
	if (token == WSPACE)
		return ("SPACE");
	else if (token == S_QUOTE)
		return ("QUOTE");
	else if (token == D_QUOTE)
		return ("DOUBLE_QUOTE");
	else if (token == BK_SL)
		return ("ESCAPE");
	else if (token == VAR)
		return ("VAR");
	else if (token == PIPE)
		return ("PIPE");
	else if (token == WORD)
		return ("WORD");
	else if (token == HERE_DOC)
		return ("HERE_DOC");
	else if (token == OUT_FILE)
		return ("DREDIR_OUT");
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
		printf("tmp->type\t\n");
		printf("-------------------------------\n");
	}
	while (tmp)
	{
		printf("%-10s\t", tmp->value);
		printf("%-10s\t\n", get_type(tmp->type));
		printf("--------------------------------\n");
		tmp = tmp->next;
	}
}

