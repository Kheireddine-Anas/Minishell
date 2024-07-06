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
        if (*p == '\'')
		{
            start = p++;
            while (*p && *p != '\'')
                p++;
            if (*p == '\'')
                p++;
            int len = p - start;
            tokens[(*num_tokens)++] = (Token){QUOTE_SINGLE, strndup(start, len)};
        }
        if (*p == '"') 
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
            tokens[(*num_tokens)++] = (Token){QUOTE_DOUBLE, strndup(start, len)};
        }
        if (isalnum(*p))
		{
            start = p;
            while (*p && (isalnum(*p) || *p == '_'))
                p++;
            
            len = p - start;
            tokens[(*num_tokens)++] = (Token){WORD, strndup(start, len)};
            continue;
        }
        fprintf(stderr, "Unexpected character: %c\n", *p);
        exit(EXIT_FAILURE);
    }
    return (tokens);
}
void parse(Token *tokens, int num_tokens)
{
    int i;

    i = 0;
    while(i < num_tokens) 
    {
        if (tokens[i].type == QUOTE_SINGLE)
             printf("Single quote: %s\n", tokens[i].value);
        else if (tokens[i].type == QUOTE_DOUBLE)
            printf("Double quote: %s\n", tokens[i].value);
        else if (tokens[i].type == WORD)
             printf("Word: %s\n", tokens[i].value);
        else if (tokens[i].type == SPACE)
            printf("Space: %s\n", tokens[i].value);
        else
        {
            fprintf(stderr, "Unexpected token type: %d\n", tokens[i].type);
            exit(EXIT_FAILURE);
        }
        i++;
    }
}
int main()
{
    const char *command =  "echo \"'hello $USER $PATH'\"'";
    int num_tokens;
    Token *tokens = tokenize(command, &num_tokens);
    
    int i = 0;
    while(i < num_tokens)
	{
        printf("Token %d: type= %d, value = %s\n", i, tokens[i].type, tokens[i].value);
		i++;
    }
    
    // Parsing des tokens
    parse(tokens, num_tokens);
	i = 0;
    while( i < num_tokens)
	{
		free(tokens[i].value);
		i++;
	}
    free(tokens);
    
    return 0;
}