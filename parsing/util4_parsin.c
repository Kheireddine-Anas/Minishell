/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util4_parsin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:19:00 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 19:07:19 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cheke_dolar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != '$')
			return (0);
		i++;
	}
	return (1);
}

char	*condition_variable(char *str, t_status **status, int index)
{
	char	*pos;
	char	*new_str;

	(void)index;
	pos = ft_strnstr(str, "$?", ft_strlen(str));
	if (pos)
	{
		new_str = replace_dollar_question_with_num(str, (*status)->status);
		if (!ft_strchr(new_str, '$'))
		{
			free(str);
			return (new_str);
		}
		free(str);
		str = NULL;
		str = ft_strdup(new_str);
		free(new_str);
	}
	return (str);
}

void	loop_de_loop_variable(char **str1, char **envp, int *k, char *variable)
{
	int		j;
	char	*tmp;

	j = 0;
	while (str1[j])
	{
		variable = ft_strchr(str1[j], '$');
		if (str1[j] && variable != NULL && !ft_strchr(str1[j], '\''))
		{
			tmp = str1[j];
			str1[j] = ft_strdup(chercher_variable(variable, envp));
			if (!str1[j] || ft_strlen(str1[j]) == 0)
				*k = 1;
			free(tmp);
		}
		j++;
	}
}

char	*loop_variable(char **str1, int i, char *str, char **envp)
{
	char	*variable;
	char	*tmp;
	int		k;

	k = 0;
	variable = NULL;
	loop_de_loop_variable(str1, envp, &k, variable);
	if (k == 1)
		str1 = create_cmmmand(str1);
	free(str);
	str = NULL;
	i = 0;
	while (str1 && str1[i])
	{
		if (str == NULL)
			str = ft_strdup("");
		tmp = str;
		str = ft_strjoin(str, str1[i]);
		free(tmp);
		i++;
	}
	free_string_array(str1);
	return (str);
}

char	*add_valu_variable(char *str, char **envp, t_status **status)
{
	char	**str1;
	int		i;
	char	*chek;
	int		index;

	if (!str)
		return (NULL);
	str1 = NULL;
	index = 0;
	i = 0;
	str = condition_variable(str, status, index);
	if (!ft_strchr(str, '$'))
		return (str);
	if (cheke_dolar(str))
		return (str);
	chek = ft_strchr(str, '$');
	if (chek && (chek[1] == '\0' || chek[1] == ' '))
		return (str);
	if (chek)
		str1 = split_variable(str);
	str = loop_variable(str1, i, str, envp);
	return (str);
}
