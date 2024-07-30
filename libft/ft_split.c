/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:11:30 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/30 12:39:25 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **result, int j)
{
	while (j > 0)
	{
		j--;
		free(result[j]);
	}
	free(result);
}

static int	ft_count_words(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static char	**ft_alloc_mem(char *s, char **result, int start, char c)
{
	int	i;
	int	len;

	i = 0;
	while (i < ft_count_words(s, c))
	{
		while (s[start] == c)
			start++;
		len = 0;
		while (s[start + len] && s[start + len] != c)
			len++;
		result[i] = ft_calloc((len + 1), sizeof(char));
		if (!result[i])
		{
			ft_free(result, i);
			return (NULL);
		}
		ft_strlcpy(result[i], &s[start], len + 1);
		start += len;
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char *s, char c)
{
	char	**result;
	int		start;

	if (!s)
		return (NULL);
	start = 0;
	result = ft_calloc((ft_count_words(s, c) + 1), sizeof(char *));
	if (result == NULL)
		return (NULL);
	result = ft_alloc_mem(s, result, start, c);
	return (result);
}
