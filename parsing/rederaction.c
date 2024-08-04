/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:47:47 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 15:54:58 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chek_out(t_cmd *lst_cmd, t_fd_ **fd_in_out, t_status **status, int i)
{
	int	fd;

	fd = 0;
	if (ft_strcmp(">", lst_cmd->rederaction[i]) == 0 || ft_strcmp(">>",
			lst_cmd->rederaction[i]) == 0)
	{
		if (ft_strlen(lst_cmd->fil_name[i]) == 0)
		{
			print_err(status);
			return (2);
		}
		if (ft_strcmp(">", lst_cmd->rederaction[i]) == 0)
			fd = open(lst_cmd->fil_name[i], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		else if (ft_strcmp(">>", lst_cmd->rederaction[i]) == 0)
			fd = open(lst_cmd->fil_name[i], O_CREAT | O_RDWR | O_APPEND, 0777);
		if (fd == -1)
		{
			(*status)->status = 1;
			erro(lst_cmd->fil_name[i]);
			return (2);
		}
		close(fd);
		(*fd_in_out)->out = i;
	}
	return (0);
}

static int	cheke_rediraction(t_cmd *lst_cmd, t_fd_ **fd_in_out,
		t_status **status, int i)
{
	if (ft_strcmp("<<", lst_cmd->rederaction[i]) == 0)
		(*fd_in_out)->in = i;
	if (ft_strcmp("<", lst_cmd->rederaction[i]) == 0)
	{
		if (ft_strlen(lst_cmd->fil_name[i]) == 0)
		{
			(*status)->status = 1;
			ft_putstr_fd("\033[33mminishell: ", 2);
			ft_putstr_fd("ambiguous redirect", 2);
			ft_putstr_fd("\033[0m", 2);
			return (2);
		}
		(*fd_in_out)->stdin = open(lst_cmd->fil_name[i], O_RDONLY);
		if ((*fd_in_out)->stdin == -1)
		{
			(*status)->status = 1;
			erro(lst_cmd->fil_name[i]);
			return (2);
		}
		close((*fd_in_out)->stdin);
		(*fd_in_out)->in = i;
	}
	if (chek_out(lst_cmd, fd_in_out, status, i) == 2)
		return (2);
	return (0);
}

static int	out_rediraction(t_cmd *lst_cmd, t_fd_ **fd_in_out,
		t_status **status)
{
	if (ft_strcmp(">>", lst_cmd->rederaction[(*fd_in_out)->out]) == 0
		|| ft_strcmp(">", lst_cmd->rederaction[(*fd_in_out)->out]) == 0)
	{
		if (ft_strcmp(">", lst_cmd->rederaction[(*fd_in_out)->out]) == 0)
			(*fd_in_out)->stdout = open(lst_cmd->fil_name[(*fd_in_out)->out],
					O_CREAT | O_WRONLY | O_TRUNC, 0777);
		else if (ft_strcmp(">>", lst_cmd->rederaction[(*fd_in_out)->out]) == 0)
			(*fd_in_out)->stdout = open(lst_cmd->fil_name[(*fd_in_out)->out],
					O_CREAT | O_RDWR | O_APPEND, 0777);
		if ((*fd_in_out)->stdout == -1)
		{
			(*status)->status = 1;
			erro(lst_cmd->fil_name[(*fd_in_out)->out]);
			return (2);
		}
		dup2((*fd_in_out)->stdout, STDOUT_FILENO);
		return (3);
	}
	return (0);
}

static int	in_rediraction(t_cmd *lst_cmd, t_fd_ **fd_in_out, t_status **status)
{
	if (ft_strcmp("<<", lst_cmd->rederaction[(*fd_in_out)->in]) == 0)
	{
		(*fd_in_out)->her_doc = open("/tmp/her_doc", O_RDWR);
		if ((*fd_in_out)->her_doc == -1)
		{
			(*status)->status = 1;
			erro("/tmp/her_doc");
			return (2);
		}
		dup2((*fd_in_out)->her_doc, STDIN_FILENO);
	}
	if (ft_strcmp("<", lst_cmd->rederaction[(*fd_in_out)->in]) == 0)
	{
		(*fd_in_out)->stdin = open(lst_cmd->fil_name[(*fd_in_out)->in],
				O_RDONLY);
		if ((*fd_in_out)->stdin == -1)
		{
			(*status)->status = 1;
			erro(lst_cmd->fil_name[(*fd_in_out)->in]);
			return (2);
		}
		dup2((*fd_in_out)->stdin, STDIN_FILENO);
	}
	return (0);
}

int	rediraction(t_cmd *lst_cmd, t_fd_ **fd_in_out, t_status **status)
{
	int	i;
	int	retu;

	i = 0;
	if (!lst_cmd || !fd_in_out)
		return (2);
	(*fd_in_out)->out = 0;
	(*fd_in_out)->in = 0;
	if (lst_cmd->rederaction[i])
	{
		while (lst_cmd->rederaction[i])
		{
			if (cheke_rediraction(lst_cmd, fd_in_out, status, i) == 2)
				return (2);
			i++;
		}
		if (in_rediraction(lst_cmd, fd_in_out, status) == 2)
			return (2);
		retu = out_rediraction(lst_cmd, fd_in_out, status);
		if (retu == 3)
			return (3);
		if (retu == 2)
			return (2);
	}
	return (0);
}
