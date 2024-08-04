/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:40:06 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 19:24:32 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fin_lop(t_fd_ **fd_in_out, int i, t_status **status)
{
	wit_process(i, &(*fd_in_out)->pids, *fd_in_out, status);
	close_file(*fd_in_out, (*fd_in_out)->fd);
}

static t_fd_	*init_and_create_cmd(t_cmd **lst_cmd, t_env **env, char *line,
		t_status **status)
{
	t_fd_	*fd_in_out;

	fd_in_out = NULL;
	fd_in_out = ft_calloc(1, sizeof(t_fd_));
	fd_in_out->stdin = 0;
	fd_in_out->stdout = 0;
	fd_in_out->her_doc = -2;
	fd_in_out->env = *env;
	fd_in_out->envp = get_erray_env(*env);
	if (!creat_cmd(lst_cmd, line, fd_in_out->envp, status))
	{
		free(fd_in_out);
		return (NULL);
	}
	fd_in_out->fd_in = dup(STDIN_FILENO);
	fd_in_out->fd_out = dup(STDOUT_FILENO);
	fd_in_out->retu_red = 0;
	fd_in_out->last = lstlast(*lst_cmd);
	return (fd_in_out);
}

void	loo_commande(t_cmd **lst_cmd, t_fd_ **fd_in_out, t_status **status)
{
	int		i;
	t_cmd	*temp;

	i = 0;
	temp = *lst_cmd;
	(*fd_in_out)->pids = ft_calloc(lstsize(*lst_cmd), sizeof(pid_t));
	while (temp)
	{
		whillop(&temp, *fd_in_out, status, &i);
		if ((*fd_in_out)->her_doc != -2)
			close((*fd_in_out)->her_doc);
		temp = temp->next;
	}
	fin_lop(fd_in_out, i, status);
	free_string_array((*fd_in_out)->envp);
	free((*fd_in_out)->pids);
	free(*fd_in_out);
	lstclear(lst_cmd);
}

static void	lop(t_env **env, char *line, t_status **status)
{
	t_fd_	*fd_in_out;
	t_cmd	*lst_cmd;

	lst_cmd = NULL;
	if (!line || !line || ft_strlen(line) == 0)
		return ;
	fd_in_out = init_and_create_cmd(&lst_cmd, env, line, status);
	if (!fd_in_out)
		return ;
	if (lst_cmd && chek_her_doc(lst_cmd, &fd_in_out, status) == 2)
	{
		close_file(fd_in_out, fd_in_out->fd);
		lstclear(&lst_cmd);
		free_string_array(fd_in_out->envp);
		free(fd_in_out);
		return ;
	}
	if (lstsize(lst_cmd) == 1)
	{
		if (chek_builting(lst_cmd, env, status, &fd_in_out) == 1)
			return ;
	}
	loo_commande(&lst_cmd, &fd_in_out, status);
}


int	main(int argc, char *argv[], char **envp)
{
	char		*line;
	t_env		*envp_new;
	t_status	*status;

	(void)argv;
	chke_arg(argc);
	envp_new = NULL;
	status = NULL;
	envp_new = get_env(envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	status = ft_calloc(1, sizeof(t_status));
	while (1)
	{
		line = readline("\033[1;33mminishell$\033[0m ");
		if (line == NULL)
			break ;
		add_history(line);
		lop(&envp_new, line, &status);
		free(line);
		line = NULL;
	}
	free_env(&envp_new);
	free(status);
}
