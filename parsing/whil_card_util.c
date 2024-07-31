/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whil_card_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:28:34 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/31 10:08:22 by ahamdi           ###   ########.fr       */
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
