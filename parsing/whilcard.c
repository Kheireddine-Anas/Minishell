/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whilcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 09:18:04 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/01 16:18:25 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

int	strnrcmp(const char *s1, const char *s2, size_t n)
{
	size_t	len1;
	size_t	len2;
	size_t	min_len;
	size_t	compare_len;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 < len2)
		min_len = len1;
	else
		min_len = len2;
	if (min_len < n)
		compare_len = min_len;
	else
		compare_len = n;
	s1 += len1 - compare_len;
	s2 += len2 - compare_len;
	while (compare_len-- > 0)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}

char	*ft_strstr(char *str, char *to_find)
{
	unsigned int	cc;
	unsigned int	i;

	if (!*to_find)
		return ((char *)str);
	cc = 0;
	while (str[cc] != '\0')
	{
		if (str[cc] == to_find[0])
		{
			i = 1;
			while (to_find[i] != '\0' && str[cc + i] == to_find[i])
				++i;
			if (to_find[i] == '\0')
				return ((char *)&str[cc]);
		}
		++cc;
	}
	return (0);
}

char	**resizer(char **entries, int *capacity, int size)
{
	char	**new_entries;
	int		new_capacity;
	int		i;

	new_capacity = *capacity * 2;
	new_entries = ft_calloc(new_capacity, sizeof(char *));
	if (!new_entries)
		perror("ft_calloc");
	i = 0;
	while (i < size)
	{
		new_entries[i] = entries[i];
		i++;
	}
	free(entries);
	*capacity = new_capacity;
	return (new_entries);
}

char	**list_directory(char *path, int *count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**entries;
	int				capacity;
	int				size;

	dir = opendir(path);
	if (!dir)
	{
		perror("opendir problem");
		exit(EXIT_FAILURE);
	}
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

int	chek_point(char *str)
{
	if (str[0] == '.')
		return (1);
	return (0);
}

char	*remove_cardt(char *str)
{
	int		i;
	int		len;
	char	*result;
	int		j;

	j = -1;
	i = -1;
	len = 0;
	while (str[++i])
		if (str[i] != '*')
			len++;
	i = -1;
	result = ft_calloc(len + 1, sizeof(char));
	while (str[++i])
		if (str[i] != '*')
			result[++j] = str[i];
	result[j] = '\0';
	return (result);
}
char	*splite(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
		{
			i++;
			break ;
		}
		i++;
	}
	res = ft_calloc(i + 1, 1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
		{
			res[i] = str[i];
			i++;
			break ;
		}
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
int	search_match(char *filename, char *pattern)
{
	int		pattern_len;
	char	*result;
	char	*strch;
	char	*strrch;
	int		l;

	l = 0;
	pattern_len = ft_strlen(pattern);
	if (pattern_len == 1 && pattern[0] == '*')
	{
		if (!chek_point(filename))
			return (1);
		return (0);
	}
	if (ft_strchr(pattern, '*') && pattern[0] != '*' && pattern[pattern_len
		- 1] != '*')
	{
		strch = ft_strchr(pattern, '*');
		if (strnrcmp(filename, strch, ft_strlen(strch) - 1) == 0)
			l++;
		strrch = splite(pattern);
		strrch[ft_strlen(strrch) - 1] = '\0';
		if (ft_strncmp(filename, strrch, ft_strlen(strrch)) == 0)
			l++;
		if (l == 2)
		{
			free(strrch);	
			return (1);
		}
		free(strrch);
	}
	if (pattern[0] == '*' && pattern[pattern_len - 1] == '*'
		&& !chek_point(filename))
	{
		pattern[pattern_len - 1] = '\0';
		result = ft_strstr(filename, pattern + 1);
		pattern[pattern_len - 1] = '*';
		if (result)
			return (1);
	}
	if (pattern[0] != '*' && pattern[pattern_len - 1] == '*')
	{
		pattern[pattern_len - 1] = '\0';
		if (ft_strncmp(filename, pattern, pattern_len - 1) == 0)
		{
			pattern[pattern_len - 1] = '*';
			return (1);
		}
		pattern[pattern_len - 1] = '*';
	}
	if (pattern[0] == '*' && pattern[pattern_len - 1] != '*'
		&& !chek_point(filename))
	{
		if (strnrcmp(filename, pattern, pattern_len - 1) == 0)
			return (1);
	}
	return (0);
}

char	**store_matches(char **entries, char *argv, int count)
{
	char	**matched_entries;
	int		match_count;
	int		j;

	match_count = 0;
	matched_entries = ft_calloc(count + 1, sizeof(char *));
	if (!matched_entries)
	{
		perror("ft_calloc");
		exit(1);
	}
	j = 0;
	while (j < count)
	{
		if (search_match(entries[j], argv))
		{
			matched_entries[match_count] = ft_strdup(entries[j]);
			(match_count)++;
		}
		j++;
	}
	return (matched_entries);
}

char	**exe_wildcard(char *argv)
{
	int		count;
	char	**entries;
	char	**matched_entries;

	count = 0;
	entries = list_directory(".", &count);
	matched_entries = store_matches(entries, argv, count);
	free_string_array(entries);
	return (matched_entries);
}
