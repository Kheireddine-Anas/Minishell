/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util5_parsin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:34:52 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 19:05:12 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*join_strings(char *s1, char *s2, char *s3, char *res)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		res[i++] = s2[j++];
	j = 0;
	while (s3[j] != '\0')
		res[i++] = s3[j++];
	res[i] = '\0';
	return (res);
}

char	*strjoi(char *s1, char *s2, char *s3)
{
	int		size_total;
	char	*res;

	if (!s1 || !s2 || !s3)
	{
		if (!s1)
			return (ft_strjoin(s2, s3));
		if (!s2)
			return (ft_strjoin(s1, s3));
		if (!s3)
			return (ft_strjoin(s1, s2));
	}
	size_total = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	res = ft_calloc(size_total, 1);
	if (!res)
		return (NULL);
	return (join_strings(s1, s2, s3, res));
}

static int	len_string(char *str)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			k++;
		i++;
	}
	return (k);
}

void	condition_re(int *i, int *j, char *nb_str, char *bufer)
{
	int	k;

	k = 0;
	while (nb_str[k])
	{
		bufer[*j] = nb_str[k];
		k++;
		(*j)++;
	}
	*i += 2;
}

char	*replace_dollar_question_with_num(char *str, int num)
{
	char	*nb_str;
	char	*bufer;
	int		i;
	int		k;
	int		j;

	j = 0;
	i = 0;
	nb_str = ft_itoa(num);
	k = len_string(str);
	bufer = ft_calloc((ft_strlen(str) - k * 2) + (ft_strlen(nb_str) * k) + 1,
			1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			condition_re(&i, &j, nb_str, bufer);
		else
			bufer[j++] = str[i++];
	}
	bufer[j] = '\0';
	free(nb_str);
	return (bufer);
}
