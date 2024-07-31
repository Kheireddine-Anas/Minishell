/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util4_parsin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:19:00 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/31 18:18:25 by ahamdi           ###   ########.fr       */
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
	char	*pos;
	char	*chek;
	if (!str)
		return (NULL);
	str1 = NULL;
	k = 0;
	i = 0;
	j = 0;
	if ((pos = ft_strnstr(str, "$?", ft_strlen(str))) != NULL)
    {
        char *new_str = malloc(strlen(str) + 50); // allocate memory for new string
        if (!new_str) return NULL;

        int index = pos - str;

        strncpy(new_str, str, index);
        new_str[index] = '\0';
        sprintf(new_str + index, "%d%s", (*status)->status, pos + 2);
		if (!ft_strchr(new_str, '$'))
		{
			return (new_str);
		}
		free(str);
        str = ft_strdup(new_str);
    }
	if (cheke_dolar(str))
	{
		free(str1);
		return (str);
	}
	chek = ft_strchr(str, '$');
	if (chek && (chek[1] == '\0' || chek[1] == ' '))
	{
		free(str1);
		return (str);
	}
	else if (chek)
		str1 = split_variable(str);
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
	if (!str1)
	{
		free(str);
		return (NULL);
	}
	if (k == 1)
		str1 = create_cmmmand(str1);
	if(k != 1)
	{
		free(str);
		str = NULL;
	}
	i = 0;
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
		// free(str1[i]);
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
