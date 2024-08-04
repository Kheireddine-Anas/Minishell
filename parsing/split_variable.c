/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:34:14 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 15:50:11 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_to_result(char **result, char *temp, int *k, int *j)
{
	if (*k > 0)
	{
		temp[*k] = '\0';
		result[(*j)++] = ft_strdup(temp);
		*k = 0;
	}
}

int	process_each_character(char **result, char *temp, char *str, int *j)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\'')
		{
			copy_to_result(result, temp, &k, j);
			temp[k++] = str[i++];
			temp[k] = '\0';
			result[(*j)++] = ft_strdup(temp);
			k = 0;
		}
		else if (str[i] == '$')
		{
			copy_to_result(result, temp, &k, j);
			temp[k++] = str[i++];
		}
		else
			temp[k++] = str[i++];
	}
	return (k);
}

char	**split_variable(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**result;
	char	*temp;

	i = 0;
	j = 0;
	k = 0;
	result = ft_calloc((ft_strlen(str) + 1), sizeof(char *));
	temp = ft_calloc(ft_strlen(str) + 1, 1);
	k = process_each_character(result, temp, str, &j);
	if (k > 0)
	{
		temp[k] = '\0';
		result[j++] = ft_strdup(temp);
	}
	result[j] = NULL;
	free(temp);
	return (result);
}
