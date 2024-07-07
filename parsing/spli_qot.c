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
        if (isalnum(*p) || *p == '_' || *p == '-')
			word(&p, &tokens, num_tokens);
    }
    return (tokens);
}

void parse(Token **tokens, int num_tokens, char **envp)
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
			printf("Single quote: %s\n", (*tokens)[i].value);
		}
        else if ((*tokens)[i].type == QUOTE_DOUBLE)
		{
			tmp = (*tokens)[i].value;
			(*tokens)[i].value = remove_doubl_qoute((*tokens)[i].value);
			free(tmp);
			tmp = NULL;
			if(ft_strchr((*tokens)[i].value, '$'))
			{
				(*tokens)[i].value = add_valu_variable((*tokens)[i].value, envp);
			}
			printf("Double quote: %s\n", (*tokens)[i].value);
		} 
        else if ((*tokens)[i].type == WORD)
		{
			if(ft_strchr((*tokens)[i].value, '$'))
			{
				(*tokens)[i].value = add_valu_variable((*tokens)[i].value, envp);
			}
			 printf("Word: %s\n", (*tokens)[i].value);
		}
        else if ((*tokens)[i].type == SPACE)
            printf("Space: %s\n", (*tokens)[i].value);
		else if ((*tokens)[i].type == IN)
			printf("Input redirection: %s\n", (*tokens)[i].value);
		else if ((*tokens)[i].type == OUT)
			printf("Output redirection: %s\n", (*tokens)[i].value);
		else if ((*tokens)[i].type == APPEND)
			printf("Append redirection: %s\n", (*tokens)[i].value);
		else if ((*tokens)[i].type == HER_DOC)
			printf("Here_doc rederaction: %s\n", (*tokens)[i].value);
		else if ((*tokens)[i].type == FILE_NAME)
			printf("File: %s\n", (*tokens)[i].value);
        else
        {
            printf("Invalid token type\n");
			exit(1);
        }
        i++;
    }
}
void leaks(void)
{
	system("leaks a.out");
}
int main(int argc ,char **argv , char **envp)
{
	(void)argc;
	(void)argv;
	atexit(leaks);
    char *command =  "/bin/ls '' 'ls'\"hg\" \"cat\" ./sript \"$PATH\" $USER ";
    int num_tokens;
    Token *tokens = tokenize(command, &num_tokens);
    int i = 0;
    while(i < num_tokens)
	{
        printf("Token %d: type= %d, value = %s\n", i, tokens[i].type, tokens[i].value);
		i++;
    }
    parse(&tokens, num_tokens, envp);
	i = 0;
    while( i < num_tokens)
	{
		free(tokens[i].value);
		i++;
	}
    free(tokens);
    
    return 0;
}