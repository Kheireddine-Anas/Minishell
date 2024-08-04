/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_focntion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:23:09 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 09:09:55 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd(t_cmd **cmd)
{
	if (cmd == NULL || *cmd == NULL)
		return ;
	if ((*cmd)->option && (*cmd)->option[0])
		free_string_array((*cmd)->option);
	else if (!(*cmd)->option[0])
		free((*cmd)->option);
	if ((*cmd)->extra_arg && (*cmd)->extra_arg[0])
		free_string_array((*cmd)->extra_arg);
	else if (!(*cmd)->extra_arg[0])
		free((*cmd)->extra_arg);
	if ((*cmd)->fil_name && (*cmd)->fil_name[0])
		free_string_array((*cmd)->fil_name);
	else if (!(*cmd)->fil_name[0])
		free((*cmd)->fil_name);
	if ((*cmd)->rederaction && (*cmd)->rederaction[0])
		free_string_array((*cmd)->rederaction);
	else if (!(*cmd)->rederaction[0])
		free((*cmd)->rederaction);
}

void	lstclear(t_cmd **lst)
{
	t_cmd	*help;
	t_cmd	*next;

	if (!*lst)
		return ;
	help = *lst;
	while (help)
	{
		next = help->next;
		free_cmd(&help);
		free(help);
		help = next;
	}
	free(help);
	*lst = NULL;
}

void	free_string_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_env(t_env **envp_new)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *envp_new;
	while (tmp)
	{
		free(tmp->key);
		free(tmp->value);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(tmp);
	*envp_new = NULL;
}
