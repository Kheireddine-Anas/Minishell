/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:34:14 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/31 16:28:30 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	result = ft_calloc((strlen(str) + 1), sizeof(char *));
	temp = ft_calloc(strlen(str) + 1, 1);
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\'')
		{
			if (k > 0)
			{
				temp[k] = '\0';
				result[j++] =  ft_strdup(temp);
				k = 0;
			}
			temp[k++] = str[i++];
			temp[k] = '\0';
			result[j++] =  ft_strdup(temp);
			k = 0;
		}
		else if (str[i] == '$')
		{
			if (k > 0)
			{
				temp[k] = '\0';
				result[j++] = ft_strdup(temp);
				k = 0;
			}
			temp[k++] = str[i++];
		}
		else
			temp[k++] = str[i++];
	}
	if (k > 0)
	{
		temp[k] = '\0';
		result[j++] =  ft_strdup(temp);
	}
	result[j] = NULL;
	free(temp);
	return (result);
}
