/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:41:45 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/03 12:54:06 by ahamdi           ###   ########.fr       */
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

int	cmd_pwd(char **str, t_status **status)
{
	char	*pwd;

	if (str[1] && ft_strcmp(str[1], "oi") != 0)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		(*status)->status = 1;
		return (1);
	}
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
	return (0);
}
static char	*cmd_pwd_cd(void)
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

int	cmd_cd(char **path, t_env **env, t_status	**status)
{
	char	*pth;
	char	*crnt;
	char	*new_pwd;
	
	crnt = getcwd(NULL, 0);
	if (path[1]&& ft_strcmp(path[1], "-L") != 0 && ft_strcmp(path[1], "-P") != 0 && ft_strcmp(path[1], "~") != 0)
	{
		if (path[1][0] == '-' )
			error_option(path[1], status);
		else if (chdir(path[1]) == -1)
		{
			error_cd(path[1], status);
			return (1);
		}
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
		{
			error_cd(pth, status);
			return (1);
		}
	}
	new_pwd = cmd_pwd_cd();
	update_env(env, "PWD",new_pwd);
	update_env(env, "OLDPWD", crnt);
	free(crnt);
	free(new_pwd);
	return (0);
}
