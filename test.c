#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

Token* tokenize(const char *input_str, int *num_tokens)
{
    Token *tokens = NULL;
	const char *start;
    *num_tokens = 0;
    int max_tokens = 10;
	int len;
    char c;
    tokens = (Token*)malloc(max_tokens * sizeof(Token));
    if (!tokens)
	{
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }
    
    const char *p = input_str;
    while (*p)
	{
        if (is_space(*p))
            p++;
		if (*p == '\'' && *(p+1) == '\'' && *(p+2) != ' ') 
            p += 2; 
        else if (*p == '\'' )
		{
            start = p++;
            while (*p && *p != '\'')
                p++; 
            if (*p == '\'')
                p++;
            len = p - start;
             tokens[(*num_tokens)].type = QUOTE_SINGLE;
			tokens[(*num_tokens)++].value = strndup(start, len);
        }
		if (*p == '\"' && *(p+1) == '\"' && *(p+2) != ' ') 
            p += 2; 
        else if (*p == '"') 
		{
            start = p++;
            while (*p && *p != '"')
			{
                if (*p == '\\')
                    p++;
                p++;
            }
            if (*p == '"')
                p++;
            len = p - start;
            tokens[(*num_tokens)].type = QUOTE_DOUBLE;
			tokens[(*num_tokens)++].value = strndup(start, len);
        }
		if(*p == '<')
		{
			start = p++;
			if(*p == '<')
			{
				len = 2;
				tokens[(*num_tokens)].type = HER_DOC;
				tokens[(*num_tokens)++].value = strndup(start, len);
				p++;
			}
			else
			{
				len = 1;
				tokens[(*num_tokens)].type = IN;
				tokens[(*num_tokens)++].value = strndup(start, len);
			}
		}
		if(*p == '>')
		{
			start = p++;
			if(*p == '>')
			{
				len = 2;
				tokens[(*num_tokens)].type = APPEND;
				tokens[(*num_tokens)++].value = strndup(start, len);
				p++;
			}
			else
			{
				len = 1;
				tokens[(*num_tokens)].type = OUT;
				tokens[(*num_tokens)++].value = strndup(start, len);
			}
		}
		if (is_space(*p))
		{
			start = p;
			while (*p && is_space(*p))
				p++;
		}
		if(*p--)
			c = *p;
		p++;
        if (isalnum(*p) || *p == '_' || *p == '-')
		{
            start = p;
            while (*p && (isalnum(*p) || *p == '_' || *p == '-'))
                p++;
            len = p - start;
			if(c == '<' || c == '>')
			{
				tokens[(*num_tokens)].type = FILE_NAME;
		   		tokens[(*num_tokens)++].value = strndup(start, len);
			}
			else
			{
				tokens[(*num_tokens)].type = WORD;
				tokens[(*num_tokens)++].value = strndup(start, len);
			}
           
        }
        
    }
    return (tokens);
}

void parse(Token **tokens, int num_tokens, char **envp)
{
    int i;

    i = 0;
    while(i < num_tokens) 
    {
        if ((*tokens)[i].type == QUOTE_SINGLE)
		{
			(*tokens)[i].value = remove_single_qoute((*tokens)[i].value);
			 printf("Single quote: %s\n", (*tokens)[i].value);
		}
        else if ((*tokens)[i].type == QUOTE_DOUBLE)
		{
			(*tokens)[i].value = remove_doubl_qoute((*tokens)[i].value);
			if(ft_strchr((*tokens)[i].value, '$'))
				(*tokens)[i].value = add_valu_variable((*tokens)[i].value, envp);
			printf("Double quote: %s\n", (*tokens)[i].value);
		} 
        else if ((*tokens)[i].type == WORD)
             printf("Word: %s\n", (*tokens)[i].value);
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
            fprintf(stderr, "Unexpected token type: %d\n", (*tokens)[i].type);
            exit(EXIT_FAILURE);
        }
        i++;
    }
}
int main(int argc ,char **argv , char **envp)
{
	(void)argc;
	(void)argv;
    const char *command =  "ls \"\" \"-l\"";
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