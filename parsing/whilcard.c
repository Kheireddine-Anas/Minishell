/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whilcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 09:18:04 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 16:25:57 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**loop(DIR *dir, int *count)
{
	char			**entries;
	int				capacity;
	int				size;
	struct dirent	*entry;

	capacity = 10;
	size = 0;
	entries = ft_calloc(capacity, sizeof(char *));
	if (!entries)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (size >= capacity)
			entries = resizer(entries, &capacity, size);
		entries[size] = ft_strdup(entry->d_name);
		size++;
		entry = readdir(dir);
	}
	closedir(dir);
	*count = size;
	return (entries);
}

char	**list_directory(char *path, int *count)
{
	DIR		*dir;
	char	**entries;

	dir = opendir(path);
	if (!dir)
	{
		perror("opendir problem");
		exit(EXIT_FAILURE);
	}
	entries = loop(dir, count);
	return (entries);
}

char	*splite(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '*')
			break ;
		i++;
	}
	res = ft_calloc(i + 1, 1);
	i = 0;
	while (str[i++])
	{
		if (str[i++] == '*')
		{
			res[i] = str[i];
			break ;
		}
		res[i] = str[i];
	}
	res[i] = '\0';
	return (res);
}

static int	lenstr(char *str)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '*' && str[i + 1] != '*') || str[i] != '*')
			len++;
		i++;
	}
	return (len);
}

char	*sqipt_whil_cart(char *str)
{
	int		i;
	char	*result;
	int		len;

	i = 0;
	if (str == NULL)
		return (NULL);
	len = lenstr(str);
	result = ft_calloc(len + 1, 1);
	if (!result)
		return (NULL);
	i = 0;
	len = 0;
	while (str[i])
	{
		if ((str[i] == '*' && str[i + 1] != '*') || str[i] != '*')
			result[len++] = str[i];
		i++;
	}
	result[len] = '\0';
	free(str);
	return (result);
}
