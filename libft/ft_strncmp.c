/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:22:47 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 09:15:32 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (!s1 || !s2)
		return (1);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i]) 
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (!s1 || !s2)
		return (1);
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i]) 
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

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
