/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remouve_double_quot.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:24:16 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 19:46:55 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**loop(char **split, t_status **status, char **envp)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (ft_strchr(split[i], '$'))
			split[i] = add_valu_variable(split[i], envp, status);
		if (!split[i])
			split[i] = ft_strdup("");
		i++;
	}
	return (split);
}

char	*condition_double(char *str, char **envp, t_status **status,
		char **result)
{
	int		i;
	char	**split;
	char	*temp;

	split = NULL;
	i = 0;
	*result = ft_strdup("");
	split = ft_split(str, '\"');
	if (!split)
		return (NULL);
	split = loop(split, status, envp);
	i = 0;
	while (split[i])
	{
		temp = *result;
		*result = ft_strjoin(*result, split[i]);
		free(temp);
		i++;
	}
	free_string_array(split);
	return (*result);
}

char	*remove_doubl_qoute(char *str, char **envp, t_status **status)
{
	int		flag;
	char	*result;
	int		i;

	flag = 0;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\"')
			flag++;
		i++;
	}
	if (flag && flag % 2 != 0)
		return (ft_strdup(str));
	else
		condition_double(str, envp, status, &result);
	return (result);
}

void	hand_double_qot(t_Token **tokens, int i, char **envp, t_status **status)
{
	char	*tmp;

	if ((*tokens)[i].value[0] == '*'
		|| (*tokens)[i].value[ft_strlen((*tokens)[i].value) - 1] == '*'
		|| ((*tokens)[i].value[0] == '*'
			&& (*tokens)[i].value[ft_strlen((*tokens)[i].value) - 1] == '*'))
		(*tokens)[i].type = WILDCARD;
	tmp = (*tokens)[i].value;
	(*tokens)[i].value = remove_doubl_qoute((*tokens)[i].value, envp, status);
	free(tmp);
	if (i == 0)
		(*tokens)[i].type = CMD;
	if ((i != 0 && (*tokens)[i - 1].type == CMD)
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

void	handl_cmd(t_Token **tokens, int i)
{
	if ((*tokens)[i].value[ft_strlen((*tokens)[i].value) - 1] == '*')
		(*tokens)[i].type = WILDCARD;
	if (i != 0 && (*tokens)[i - 1].type == IN)
		(*tokens)[i].type = FILE_IN;
	else if (i != 0 && (*tokens)[i - 1].type == HER_DOC)
		(*tokens)[i].type = LIM;
	else if (i != 0 && ((*tokens)[i - 1].type == OUT || (*tokens)[i
		- 1].type == APPEND))
		(*tokens)[i].type = FILE_OUT;
}
