/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utul_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:06:03 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 16:09:35 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_erray_env(t_env *env)
{
	int		i;
	char	**env_arr;
	int		len;

	if (!env)
		return (NULL);
	i = 0;
	len = size_(env);
	env_arr = malloc(sizeof(char *) * (len + 1));
	if (!env_arr)
		return (NULL);
	env_arr[len] = NULL;
	while (env)
	{
		env_arr[i] = strjoi(env->key, "=", env->value);
		env = env->next;
		i++;
	}
	return (env_arr);
}

int	print_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (1);
	tmp = env;
	while (tmp)
	{
		if (ft_strlen(tmp->value) != 0)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

void	print_err(t_status **status)
{
	(*status)->status = 1;
	ft_putstr_fd("\033[33mminishell: ", 2);
	ft_putstr_fd("ambiguous redirect", 2);
	ft_putstr_fd("\033[0m", 2);
	ft_putstr_fd("\n", 2);
}
