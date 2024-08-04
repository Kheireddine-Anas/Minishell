/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whil_card_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:20:44 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 09:44:13 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	condition1_search_match(char *filename, char *pattern,
		int pattern_len)
{
	char	*result;

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
	return (0);
}

static int	condition2_search_match(char *filename, char *pattern,
		int pattern_len)
{
	int		l;
	char	*strch;
	char	*strrch;

	l = 0;
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
	return (0);
}

int	search_match(char *filename, char *pattern)
{
	int		pattern_len;

	pattern_len = ft_strlen(pattern);
	if (pattern_len == 1 && pattern[0] == '*')
	{
		if (!chek_point(filename))
			return (1);
		return (0);
	}
	if (condition2_search_match(filename, pattern, pattern_len) == 1)
		return (1);
	if (condition1_search_match(filename, pattern, pattern_len) == 1)
		return (1);
	if (pattern[0] == '*' && pattern[pattern_len - 1] != '*'
		&& !chek_point(filename))
	{
		if (strnrcmp(filename, pattern, pattern_len - 1) == 0)
			return (1);
	}
	return (0);
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
