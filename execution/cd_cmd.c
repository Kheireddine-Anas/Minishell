/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:41:45 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/20 11:29:44 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_valus(t_env *envs, char *srch)
{
	t_env	*tmp;

	tmp = envs;
	while (tmp)
	{
		if (!(strcmp(tmp->key, srch)))
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*cmd_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	return (pwd);
}

void	error_cd(char *str, t_status	**status)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	(*status)->status = 1;
}

void	error_option(char *str, t_status	**status)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": invalid option \n", 2);
	ft_putstr_fd("cd: usage: cd [-L|-P] [dir]\n", 2);
	(*status)->status = 1;
}

void	cmd_cd(char **path, t_env **env, t_status	**status)
{
	char	*pth;
	char	*crnt;

	crnt = getcwd(NULL, 0);
	if (path[1])
	{
		if (path[1][0] == '-' && path[1][0] != 'L' && path[1][0] != 'P')
			error_option(path[1], status);
		else if (chdir(path[1]) == -1)
			error_cd(path[1], status);
	}
	else
	{
		pth = get_valus(*env, "HOME");
		if (!pth)
		{
			ft_putstr_fd("Set HOME env\n", 2);
			(*status)->status = 1;
		}
		else if (chdir(pth) == -1)
			error_cd(pth, status);
	}
	update_env(env, "PWD", cmd_pwd());
	update_env(env, "OLDPWD", crnt);
}
