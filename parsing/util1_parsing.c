/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:36:15 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/23 18:12:40 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*process_quotes(char *str, char *dst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[0] == '\'' && str[strlen(str) - 1] == '\'' && strlen(str) != 1)
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
		if (str[1] && str[1] == '*')
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

static char	*process_double_quotes(char *str, char *dst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[0] == '"' && str[strlen(str) - 1] == '"' && strlen(str) != 1)
	{
		while (str[i])
		{
			if (str[i] != '\"')
				dst[j++] = str[i];
			i++;
		}
	}
	else
	{
		if (str[1] && str[1] == '*')
		{
			while (str[i])
			{
				if (str[i] != '\"')
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

char	*remove_doubl_qoute(char *str)
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
		exit(EXIT_FAILURE);
	}
	return (process_double_quotes(str, dst));
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
