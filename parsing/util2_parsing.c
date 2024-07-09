#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

void out(char **p, Token **tokens, int *num_tokens)
{
	char	*start;
	int		len;

	start = (*p)++;
	if(**p == '>')
	{
		len = 2;
		(*tokens)[(*num_tokens)].type = APPEND;
		(*tokens)[(*num_tokens)++].value = strndup(start, len);
		(*p)++;
	}
	else
	{
		len = 1;
		(*tokens)[(*num_tokens)].type = OUT;
		(*tokens)[(*num_tokens)++].value = strndup(start, len);
	}
}

void in(char **p, Token **tokens, int *num_tokens)
{
	char	*start;
	int		len;

	start = (*p)++;
	if(**p == '<')
	{
		len = 2;
		(*tokens)[(*num_tokens)].type = HER_DOC;
		(*tokens)[(*num_tokens)++].value = strndup(start, len);
		(*p)++;
	}
	else
	{
		len = 1;
		(*tokens)[(*num_tokens)].type = IN;
		(*tokens)[(*num_tokens)++].value = strndup(start, len);
	}
}

void word(char **p, Token **tokens, int *num_tokens)
{
	char	*start;
	int		len;
    char	c;
	char	h;
    if(*num_tokens != 0)
        c = *(*p- 1);
	h = **p;
	start = *p;
    while (**p != '\0' &&  **p != '$' && **p != '\"' && **p != '\'' && !is_space(**p) && **p != '|')
        (*p)++;
    len = (*p) - start;
	if(h == '-')
		(*tokens)[(*num_tokens)].type = OPTION;
	else if(c == '<')
		(*tokens)[(*num_tokens)].type = FILE_IN;
	else if (c == '>')
		(*tokens)[(*num_tokens)].type = FILE_OUT;
	else
		(*tokens)[(*num_tokens)].type = WORD;
	(*tokens)[(*num_tokens)++].value = strndup(start, len);
}

void quot(char **p, Token **tokens, int *num_tokens)
{
	char *start;
	int len;
    char c;

	if (**p == '\'' )
	{
		start = (*p)++;
    	while (**p && **p != '\'')
        	(*p)++; 
    	if (**p == '\'')
        	(*p)++;
    	len = *p - start;
    	(*tokens)[(*num_tokens)].type = QUOTE_SINGLE;
		(*tokens)[(*num_tokens)++].value = strndup(start, len);
	}
	if (**p == '"') 
	{
        start = (*p)++;
        while (**p && **p != '"')
		{
            if (**p == '\\')
                (*p)++;
            (*p)++;
        }
        if (**p == '"')
            (*p)++;
        len = *p - start;
        (*tokens)[(*num_tokens)].type = QUOTE_DOUBLE;
		(*tokens)[(*num_tokens)++].value = strndup(start, len);
    }
    
    if (**p == '/' || **p == '.' || **p == '$')
	{
        c = **p;
		start = (*p)++;
		while(**p != ' ' && **p && **p != '\"' && **p != '\"')
			(*p)++;
		len = *p - start;
        if(c == '$')
            (*tokens)[(*num_tokens)].type = VARIABLE;
        else if(c == '/' || c == '.')
            (*tokens)[(*num_tokens)].type = CMD;
        else
		    (*tokens)[(*num_tokens)].type = WORD;
		(*tokens)[(*num_tokens)++].value = strndup(start, len);
	}
}