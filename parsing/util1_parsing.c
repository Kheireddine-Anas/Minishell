/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:36:15 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/03 13:30:14 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*process_quotes(char *str, char *dst)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			k++;
		i++;
	}
	i = 0;
	if (str[0] == '\'' && str[strlen(str) - 1] == '\'' && strlen(str) > 1 && k != 0 && k % 2 == 0)
	{
		while (str[i])
		{
			if (str[i] != '\'' && (str[i + 1] != '{' || str[i - 1] != '}'))
				dst[j++] = str[i];
			i++;
		}
	}
	else
	{
		i = 0;
		if (k != 0 && k % 2 == 0)
		{
			while (str[i])
			{
				if (str[i] != '\'')
					dst[j++] = str[i];
				i++;
			}
		}
		else
		{
			while (str[i])
			{
				dst[j++] = str[i];
				i++;
			}
		}
	}
	dst[j] = '\0';
	return (dst);
}

char	*remove_single_qoute(char *str)
{
	char	*dst;
	int		len;

	if (!str)
		return (NULL);
	len = strlen(str);
	dst = ft_calloc(len + 1, 1);
	if (!dst)
	{
		perror("Allocation error");
		return (NULL);
	}
	return (process_quotes(str, dst));
}

char	*remove_doubl_qoute(char *str, char **envp, t_status **status)
{
	int		flag;
	char	**split;
	char	*result;
	char	*temp;
	int		i;

	flag = 0;
	result = ft_strdup("");
	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\"')
			flag++;
		;
		i++;
	}
	if (flag && flag % 2 != 0)
		return (ft_strdup(str));
	else
	{
		split = ft_split(str, '\"');
		if (!split)
			return (NULL);
		i = 0;
		while (split[i])
		{
			if (ft_strchr(split[i], '$'))
				split[i] = add_valu_variable(split[i], envp, status);
			if (!split[i])
				split[i] = ft_strdup("");
			i++;
		}
		i = 0;
		while (split[i])
		{
			temp = result;
			result = ft_strjoin(result, split[i]);
			free(temp);
			i++;
		}
	}
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (result);
}

char	*chercher_variable(char *str, char **envp)
{
	int		i;
	char	*variable;
	i = 0;

	variable = "\0";
	if (!str)
		return (variable);
	str++;
	if (*str != '\0')
	{
		str = ft_strjoin(str, "=");
		while (envp[i])
		{
			if (ft_strnstr(envp[i], str, ft_strlen(envp[i])) != NULL)
			{
				variable = ft_strnstr(envp[i], str, ft_strlen(envp[i]))
					+ ft_strlen(str);
				break ;
			}
			i++;
		}
		free(str);
	}
	return (variable);
}
