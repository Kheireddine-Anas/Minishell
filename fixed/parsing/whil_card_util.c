/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whil_card_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:28:34 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/26 09:09:15 by akheired         ###   ########.fr       */
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
	return (resu);
}
