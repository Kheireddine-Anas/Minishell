/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fontion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:14:25 by ahamdi            #+#    #+#             */
/*   Updated: 2024/06/28 10:19:03 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*strjoi(char *s1, char *s2, char *s3)
{
    int		size_total;
    char	*res;
    int		i;
    int		j;

    j = 0;
    i = 0;
    if (!s1 || !s2 || !s3)
	{
		if(!s1)
			return (ft_strjoin(s2, s3));
		if(!s2)
			return (ft_strjoin(s1, s3));
		if(!s3)
			return (ft_strjoin(s1, s2));
	}
    size_total = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
    res = ft_calloc(size_total, 1);
    if (!res)
        return (NULL);
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

int	lstsize(env_t *lst)
{
	env_t	*help;
	int		len;

	len = 0;
	help = lst;
	while (help != NULL)
	{
		help = help -> next;
		len++;
	}
	return (len);
}

env_t	*lstlast(env_t *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst-> next;
	return (lst);
}
void	add_back(env_t **lst, env_t *new)
{
	env_t	*last;

	if (!*lst)
		*lst = new;
	else
	{
		last = lstlast(*lst);
		last->next = new;
	}
}
