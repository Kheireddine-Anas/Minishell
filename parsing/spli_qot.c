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
		if(*num_tokens >= max_tokens)
			tokens = realloc_cmd(&tokens, &max_tokens);
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
			if(((get_path(envp, (*tokens)[i].value, 0) != NULL) || access((*tokens)[i].value, X_OK) == 0) && (ft_strlen((*tokens)[i].value)) > 1)
				(*tokens)[i].type = CMD;
			free(tmp);
		}
        else if ((*tokens)[i].type == QUOTE_DOUBLE)
		{
			tmp = (*tokens)[i].value;
			(*tokens)[i].value = remove_doubl_qoute((*tokens)[i].value);
			free(tmp);
			if(ft_strchr((*tokens)[i].value, '$'))
			{
				(*tokens)[i].type = VARIABLE;
				(*tokens)[i].value = add_valu_variable((*tokens)[i].value, envp);
			}
			else if(((get_path(envp, (*tokens)[i].value, 0) != NULL) || access((*tokens)[i].value, X_OK) == 0) && (ft_strlen((*tokens)[i].value)) > 1)
				(*tokens)[i].type = CMD;
		} 
        else if ((*tokens)[i].type == WORD)
		{
			if((get_path(envp, (*tokens)[i].value, 0) != NULL))
				(*tokens)[i].type = CMD;
		}
		else if((*tokens)[i].type == VARIABLE)
		{
			if(ft_strchr((*tokens)[i].value, '$'))
			{
				(*tokens)[i].value = add_valu_variable((*tokens)[i].value, envp);
			}
		}
        i++;
    }
}

t_cmd	*lstnew(char *command, char **env)
{
	int		i;
	t_cmd	*new;
	int		j;
	int		k;
	Token	*tokens;
	int		num_tokens = 0;
	j = 0;
	k = 0;
	i = 0;
	printf("****999\n");
	// printf("%s\n",command);
	tokens = tokenize(command, &num_tokens);
	i = 0;
	while (i < num_tokens)
	{
		printf("type: %d\n", tokens[i].type);
		printf("value: %s\n", tokens[i].value);
		i++;
	
	}
	i = 0;
	parse(&tokens, num_tokens, env);
	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->option = ft_calloc(5,sizeof(char *));
	new->extra_arg = ft_calloc(5,sizeof(char *));
	new->in = NULL;
	new->out = NULL;
	while(i < num_tokens)
	{
		if(tokens[i].type == CMD || tokens[i].type == WORD)
			new->cmd =  ft_strdup(tokens[i].value);
		else if(tokens[i].type == IN || tokens[i].type == HER_DOC)
			new->in =  ft_strdup(tokens[i].value);
		else if(tokens[i].type == OUT || tokens[i].type == APPEND)
			new->out = ft_strdup(tokens[i].value);
		else if((tokens[i].type == WORD && tokens[i].value[0] == '-') || tokens[i].type == VARIABLE )
		{
			new->option[j] = ft_strdup(tokens[i].value);
			j++;
		}
		else if(tokens[i].type == FILE_NAME)
		{
			new->extra_arg[k] = ft_strdup(tokens[i].value);
			k++;
		}
		i++;
	}
	new->option[j] = NULL;
	new->extra_arg[k] = NULL;
	new->next = NULL;
	return (new);
}
