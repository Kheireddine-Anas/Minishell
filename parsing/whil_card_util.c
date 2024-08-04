/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whil_card_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:28:34 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 09:19:38 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remouve_single_double_qout(char *str)
{
	int		i;
	int		len;
	char	*resu;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			len++;
		i++;
	}
	resu = ft_calloc(len + 1, 1);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			resu[len++] = str[i];
		i++;
	}
	resu[len] = '\0';
	free(str);
	return (resu);
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
