/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:40:06 by ahamdi            #+#    #+#             */
/*   Updated: 2024/07/22 21:25:41 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fin_lop(t_fd_ *fd_in_out, int i, t_status **status)
{
	wit_process(i, &fd_in_out->pids, fd_in_out, status);
	close_file(fd_in_out, fd_in_out->fd);
	free(fd_in_out);
}

static t_fd_	*init_and_create_cmd(t_cmd **lst_cmd, t_env **env, char *line,
		t_status **status)
{
	t_fd_	*fd_in_out;

	fd_in_out = ft_calloc(1, sizeof(t_fd_));
	fd_in_out->stdin = 0;
	fd_in_out->stdout = 0;
	fd_in_out->her_doc = 0;
	fd_in_out->envp = get_erray_env(*env);
	creat_cmd(lst_cmd, line, fd_in_out->envp, status);
	if (!lst_cmd)
	{
		printf("9999999\n");
		(*status)->status = 1;
		return (NULL);
	}
	fd_in_out->fd_in = dup(STDIN_FILENO);
	fd_in_out->fd_out = dup(STDOUT_FILENO);
	fd_in_out->retu_red = 0;
	fd_in_out->last = lstlast(*lst_cmd);
	return (fd_in_out);
}

static int	whillop(t_cmd	*lst_cmd, t_fd_	*fd_in_out, 
		t_status **status, int i)
{
	fd_in_out->retu_red = rediraction(lst_cmd, &fd_in_out, status);
	if (fd_in_out->retu_red == 2)
		return (1);
	if (pipe(fd_in_out->fd) == -1)
		hand_error(status, "pipe");
	fd_in_out->pids[i] = fork();
	if (fd_in_out->pids[i] == -1)
		hand_error(status, "fork");
	if (fd_in_out->pids[i] == 0 && lst_cmd != fd_in_out->last)
		child_process(lst_cmd, fd_in_out->envp, fd_in_out->fd, &fd_in_out);
	else if (fd_in_out->pids[i] == 0 && lst_cmd == fd_in_out->last)
		fin_commande(lst_cmd, fd_in_out->envp);
	else if (fd_in_out->pids[i] > 0)
		parent_prossuce(fd_in_out->fd, &fd_in_out, i);
	whilloop(fd_in_out->fd);
	return (0);
}

static void	lop(t_env **env, char *line, t_status **status)
{
	int		i;
	t_fd_	*fd_in_out;
	t_cmd	*lst_cmd;

	if(!line || ft_strlen(line) == 0)
		return ;
	lst_cmd = NULL;
	i = 0;
	fd_in_out = init_and_create_cmd(&lst_cmd, env, line, status);
	if (!fd_in_out)
		return ;
	if ((*lst_cmd->option) && 
		builting(fd_in_out->last, env, status, &fd_in_out) == 1)
	{
		close_file(fd_in_out, fd_in_out->fd);
		return ;
	}
	if (!lst_cmd || !fd_in_out->envp)
		return ;
	fd_in_out->pids = ft_calloc(lstsize(lst_cmd), sizeof(pid_t));
	while (lst_cmd)
	{
		if (whillop(lst_cmd, fd_in_out, status, i) == 1)
			return ;
		lst_cmd = lst_cmd->next;
		i++;
	}
	fin_lop(fd_in_out, i, status);
	lstclear(&lst_cmd);
}

int	main(int argc, char *argv[], char **envp)
{
	char		*line;
	t_env		*envp_new;
	t_status	*status;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	envp_new = get_env(envp);
	signal(SIGINT, handle_sigint);
	status = ft_calloc(1, sizeof(t_status));
	while (1)
	{
		line = readline("\033[1;33mmini-shell> \033[0m");
		if (line == NULL)
			break ;
		add_history(line);
		lop(&envp_new, line, &status);
		free(line);
		line = NULL;
	}
	free(status);
}
