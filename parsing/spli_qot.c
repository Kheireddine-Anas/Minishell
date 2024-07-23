/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spli_qot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:27:17 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/23 15:59:39 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_Token	*tokenize(char *p, int *num_tokens)
{
	t_Token	*tokens;
	int		max_tokens;
	tokens = NULL;
	max_tokens = 2;
	*num_tokens = 0;
	tokens = ft_calloc(max_tokens, sizeof(t_Token));
	if (!tokens)
		error_alocation();
	while (*p)
		condition(&p, &tokens, num_tokens, &max_tokens);
	return (tokens);
}

void	parse(t_Token **tokens, int num_tokens, char **envp, t_status **status)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < num_tokens )
	{
		if ((*tokens)[i].type == WORD)
		{
			if (i != 0 && (*tokens)[i - 1].type == IN)
				(*tokens)[i].type = FILE_IN;
			else if (i != 0 && (*tokens)[i - 1].type == HER_DOC)
				(*tokens)[i].type = LIM;
			else if (i != 0 && ((*tokens)[i - 1].type == OUT 
				|| (*tokens)[i - 1].type == APPEND))
				(*tokens)[i].type = FILE_OUT;
			else if ((*tokens)[i].value[ft_strlen((*tokens)[i].value) - 1] == '*')
				(*tokens)[i].type = WHILCART;
		}
		else if ((*tokens)[i].type == QUOTE_SINGLE)
		{
			tmp = (*tokens)[i].value;
			(*tokens)[i].value = remove_single_qoute((*tokens)[i].value);
			free(tmp);
			if (i == 0)
				(*tokens)[i].type = CMD;
			else if ((i != 0 && (*tokens)[i - 1].type == CMD)
				|| (*tokens)[i].value[0] == '-')
				(*tokens)[i].type = OPTION;
			if (i != 0 && (*tokens)[i - 1].type == IN)
				(*tokens)[i].type = FILE_IN;
			else if (i != 0 && (*tokens)[i - 1].type == HER_DOC)
				(*tokens)[i].type = LIM;
			else if (i != 0 && ((*tokens)[i - 1].type == OUT ||
				(*tokens)[i - 1].type == APPEND))
				(*tokens)[i].type = FILE_OUT;
		}
		else if ((*tokens)[i].type == QUOTE_DOUBLE)
		{
			tmp = (*tokens)[i].value;
			(*tokens)[i].value = remove_doubl_qoute((*tokens)[i].value);
			free(tmp);
			if (ft_strchr((*tokens)[i].value, '$'))
			{
				(*tokens)[i].type = VARIABLE;
				(*tokens)[i].value = add_valu_variable((*tokens)[i].value, envp,
						status);
				if (i != 0 && (*tokens)[i - 1].type == CMD)
					(*tokens)[i].type = OPTION;
			}
			if (i == 0)
				(*tokens)[i].type = CMD;
			if ((i != 0 && (*tokens)[i - 1].type == CMD)
				|| (*tokens)[i].value[0] == '-')
				(*tokens)[i].type = OPTION;
			if (i != 0 && (*tokens)[i - 1].type == IN)
				(*tokens)[i].type = FILE_IN;
			else if (i != 0 && (*tokens)[i - 1].type == HER_DOC)
				(*tokens)[i].type = LIM;
			else if (i != 0 && ((*tokens)[i - 1].type == OUT 
				|| (*tokens)[i - 1].type == APPEND))
				(*tokens)[i].type = FILE_OUT;
		}
		else if ((*tokens)[i].type == VARIABLE)
		{
			if (ft_strchr((*tokens)[i].value, '$'))
				(*tokens)[i].value = add_valu_variable((*tokens)[i].value, envp,
						status);
			if (i == 0)
				(*tokens)[i].type = CMD;
			if (i != 0 && (*tokens)[i - 1].type == CMD)
				(*tokens)[i].type = OPTION;
		}
		else if((*tokens)[i].type == CMD)
		{
			if (ft_strlen((*tokens)[i].value) == 2 && (*tokens)[i].value[0] == '.' && (*tokens)[i].value[1] == '*')
				(*tokens)[i].type = WHILCART;
		}
		i++;
	}
}
// int main(int argc, char **argv, char **envp)
// {
//    	t_Token  *tokens;
// 	t_status	*status;
// 	int num_tokens = 0;
// 	int i = 0;
	
// 	char *p = "ls *.";
// 	status = ft_calloc(1, sizeof(t_status));
//     tokens = tokenize(p, &num_tokens);
// 	parse(&tokens, num_tokens, envp, &status);
// 	while(i < num_tokens)
// 	{
// 		printf("type: %d ", tokens[i].type);
// 		printf("value: %s\n", tokens[i].value);
// 		i++;
// 	}

// }