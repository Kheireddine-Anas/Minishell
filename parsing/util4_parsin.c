/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util4_parsin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:19:00 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/26 13:30:03 by ahamdi           ###   ########.fr       */
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

char	*add_valu_variable(char *str, char **envp, t_status **status)
{
	char	**str1;
	int		k;
	int		i;
	int		j;
	char	*variable;
	char	*tmp;

	if (!str)
		return (NULL);
	str1 = NULL;
	k = 0;
	i = 0;
	j = 0;
	if (ft_strcmp("$?", str) == 0)
		return (ft_itoa((*status)->status));
	if (cheke_dolar(str))
		return (str);
	if (ft_strchr(str, '$'))
		str1 = split_variable(str);
	if (!str1)
		return (NULL);
	while (str1[j])
	{
		variable = ft_strchr(str1[j], '$');
		if (str1[j] && variable != NULL && !ft_strchr(str1[j], '\''))
		{
			tmp = str1[j];
			str1[j] = chercher_variable(variable, envp);
			if (!str1[j] || ft_strlen(str1[j]) == 0)
				k = 1;
			free(tmp);
		}
		j++;
	}
	if (k == 1)
		str1 = create_cmmmand(str1);
	free(str);
	str = NULL;
	while (str1 && str1[i])
	{
		if (str == NULL)
			str = ft_strdup(str1[i]);
		else
		{
			tmp = str;
			str = ft_strjoin(str, str1[i]);
			free(tmp);
		}
		i++;
	}
	while (str1[i])
	{
		free(str1[i]);
		i++;
	}
	free(str1);
	return (str);
}

int	st_2derra(char **str, int k)
{
	int	i;

	str[k] = NULL;
	i = 0;
	while (str[i])
		i++;
	return (i);
}
