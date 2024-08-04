/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spli_qot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:27:17 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 19:47:03 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handl_dploar_condition(t_Token **tokens, int i)
{
	if ((*tokens)[i].value == NULL)
		(*tokens)[i].type = ERRRO;
	else if (i - 1 != 0 && (*tokens)[i].value != NULL
		&& cheke_dolar((*tokens)[i].value) == 1)
		(*tokens)[i].value = NULL;
	else if (i != 0 && (*tokens)[i - 1].type == CMD)
		(*tokens)[i].type = OPTION;
	else if (i != 0 && ((*tokens)[i - 1].type == OUT || (*tokens)[i
		- 1].type == APPEND))
		(*tokens)[i].type = FILE_OUT;
	else if (i != 0 && ((*tokens)[i - 1].type == IN || (*tokens)[i
		- 1].type == HER_DOC))
		(*tokens)[i].type = FILE_OUT;
}

void	hand_dolar_inword(t_Token **tokens, int i, char **envp,
		t_status **status)
{
	if (i != 0 && (*tokens)[i - 1].type == HER_DOC)
		(*tokens)[i].type = LIM;
	else
	{
		(*tokens)[i].type = VARIABLE;
		(*tokens)[i].value = add_valu_variable((*tokens)[i].value, envp,
				status);
	}
	if ((*tokens)[i].value == NULL && i > 0 && ((*tokens)[i - 1].type == IN
			|| (*tokens)[i - 1].type == OUT || (*tokens)[i - 1].type == APPEND))
		(*tokens)[i].value = ft_strdup("");
	else
		handl_dploar_condition(tokens, i);
}

void	hand_word(t_Token **tokens, int i, char **envp, t_status **status)
{
	if (ft_strchr((*tokens)[i].value, '$')
		&& (*tokens)[i].value[ft_strlen((*tokens)[i].value) - 1] != '$')
		hand_dolar_inword(tokens, i, envp, status);
	else if (ft_strchr((*tokens)[i].value, '*'))
		(*tokens)[i].type = WILDCARD;
	else if (i != 0 && (*tokens)[i - 1].type == IN)
		(*tokens)[i].type = FILE_IN;
	else if (i != 0 && (*tokens)[i - 1].type == HER_DOC)
		(*tokens)[i].type = LIM;
	else if (i != 0 && ((*tokens)[i - 1].type == OUT || (*tokens)[i
		- 1].type == APPEND))
		(*tokens)[i].type = FILE_OUT;
	else if ((*tokens)[i].value[ft_strlen((*tokens)[i].value) - 1] == '*')
		(*tokens)[i].type = WILDCARD;
}

void	hand_sigle_qot(t_Token **tokens, int i)
{
	char	*tmp;

	tmp = (*tokens)[i].value;
	if ((*tokens)[i].value[0] == '*'
		|| (*tokens)[i].value[ft_strlen((*tokens)[i].value) - 1] == '*'
		|| ((*tokens)[i].value[0] == '*'
			&& (*tokens)[i].value[ft_strlen((*tokens)[i].value) - 1] == '*'))
		(*tokens)[i].type = WILDCARD;
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
	else if (i != 0 && ((*tokens)[i - 1].type == OUT || (*tokens)[i
		- 1].type == APPEND))
		(*tokens)[i].type = FILE_OUT;
}

void	parse(t_Token **tokens, int num_tokens, char **envp, t_status **status)
{
	int	i;

	i = 0;
	while (i < num_tokens)
	{
		if ((*tokens)[i].type == WORD)
			hand_word(tokens, i, envp, status);
		else if ((*tokens)[i].type == QUOTE_SINGLE)
			hand_sigle_qot(tokens, i);
		else if ((*tokens)[i].type == QUOTE_DOUBLE)
			hand_double_qot(tokens, i, envp, status);
		else if ((*tokens)[i].type == CMD)
			handl_cmd(tokens, i);
		i++;
	}
}
