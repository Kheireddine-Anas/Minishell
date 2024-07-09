#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


Token* tokenize(char *p, int *num_tokens)
{
    Token *tokens;
    int max_tokens;
	tokens = NULL;
	max_tokens = 10;
	*num_tokens = 0;
    tokens = ft_calloc(max_tokens , sizeof(Token));
    if (!tokens)
		error_alocation();
    while (*p)
	{
        if (is_space(*p))
            p++;
		if ((*p == '\'' && *(p+1) == '\'' && *(p+2) != ' ' )|| (*p == '\"' && *(p+1) == '\"' && *(p+2) != ' ')) 
            p += 2; 
        quot(&p, &tokens, num_tokens);
		if(*p == '<')
			in(&p, &tokens, num_tokens);
		if(*p == '>')
			out(&p,&tokens, num_tokens);
		if (is_space(*p))
		{
			while (*p && is_space(*p))
				p++;
		}
		if (*p == '|')
		{
			tokens[(*num_tokens)].type = PIP;
			tokens[(*num_tokens)++].value = strndup(p, 1);
			p++;
		}
        if (*p != '\0' &&  *p != '$' && *p != '\"' && *p != '\'' && !is_space(*p) && *p != '<' && *p != '>')
			word(&p, &tokens, num_tokens);
		if(*num_tokens >= max_tokens)
			tokens = realloc_cmd(&tokens, &max_tokens);
    }
    return (tokens);
}

void parse(Token **tokens, int num_tokens, char **envp, t_cmd	**new)
{
    int i;

    i = 0;
	char *tmp;

    while(i < num_tokens) 
    {
        if ((*tokens)[i].type == QUOTE_SINGLE)
		{
			tmp = (*tokens)[i].value;
			(*tokens)[i].value = remove_single_qoute((*tokens)[i].value);
			free(tmp);
			if((*tokens)[i].value[0] == '\'')
				(*new)->single = 1;
			if (i == 0)
				(*tokens)[i].type = CMD;
			else if ((*tokens)[i - 1].type == CMD || (*tokens)[i].value[0] == '-')
				(*tokens)[i].type = OPTION;
		}
        else if ((*tokens)[i].type == QUOTE_DOUBLE)
		{
			tmp = (*tokens)[i].value;
			(*tokens)[i].value = remove_doubl_qoute((*tokens)[i].value);
			free(tmp);
			if((*tokens)[i].value[0] == '\"')
				(*new)->double_q = 1;
			if(ft_strchr((*tokens)[i].value, '$'))
			{
				(*tokens)[i].type = VARIABLE;
				(*tokens)[i].value = add_valu_variable((*tokens)[i].value, envp);
				if (i != 0 && (*tokens)[i - 1].type == CMD)
					(*tokens)[i].type = OPTION;
			}
			if (i == 0)
				(*tokens)[i].type = CMD;
			if ((*tokens)[i - 1].type == CMD || (*tokens)[i].value[0] == '-')
				(*tokens)[i].type = OPTION;
		} 
		else if((*tokens)[i].type == VARIABLE)
		{
			if(ft_strchr((*tokens)[i].value, '$'))
				(*tokens)[i].value = add_valu_variable((*tokens)[i].value, envp);
			if (i == 0)
				(*tokens)[i].type = CMD;
			if (i != 0 && (*tokens)[i - 1].type == CMD)
				(*tokens)[i].type = OPTION;
		}
        i++;
    }
}


// int main (int argc ,char ** argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
//     char *str = "ls -l -a <test >hamdi ";
//     Token *tokens;
//     int i = 0;
//     int num_tokens = 0;
// 	t_cmd	*new;
// 		new = ft_calloc(1, sizeof(t_cmd));
// 	if (!new)
// 		return (0);
//     tokens = tokenize(str, &num_tokens);
// 	parse(&tokens, num_tokens, envp,&new);
//     if (!tokens)
//         exit(EXIT_FAILURE);
// 	while (i < num_tokens)
//     {
//         printf("type: %d,value: %s\n", tokens[i].type, tokens[i].value);
// 		i++;
//     }
//     return 0;
// }
// else if (ft_strcmp(tmp->content, "$?") == 1)
// 			{
// 				free(tmp->content);
// 				tmp->content = ft_itoa(g_glob.g_exit);
// 				tmp->type = WORD;
// 			}
// har	*ft_dollar(char *input, int *i)
// {
// 	char	var[10];

// 	while (input[*i])
// 	{
// 		(*i)++;
// 		if (input[*i] == '$')
// 			return (ft_strdup("$$"));
// 		else if (input[*i] == '@')
// 			return (ft_strdup(""));
// 		else if (input[*i] == '?')
// 			return (ft_strdup("$?"));
// 		else if (ft_num(input[*i]))
// 		{
// 			var[0] = '$';
// 			var[1] = input[*i];
// 			var[2] = '\0';
// 			return (ft_strdup(var));
// 		}
// 		else if (ft_alpha(input[*i]) || input[*i] == '_')
// 			return (set_var(input, i));
// 		else
// 			return ((*i)--, ft_strdup("$"));
// 	}
// 	return (ft_strdup("$"));
// }