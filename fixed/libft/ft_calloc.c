/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:09:05 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/24 22:57:58 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t numel, size_t size_el)
{
	size_t	size_totat ;
	void	*ma;

	ma = NULL;
	if (!size_el)
		size_el = 1;
	size_totat = numel * size_el;
	if (size_el != 0 && numel != size_totat / size_el)
		return (NULL);
	ma = malloc(size_totat);
	if (ma != NULL)
		ft_bzero (ma, size_totat);
	return (ma);
}
