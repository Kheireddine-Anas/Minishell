/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:08:52 by ahamdi            #+#    #+#             */
/*   Updated: 2023/12/20 21:08:58 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *m, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)m;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}