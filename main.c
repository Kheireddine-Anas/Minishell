/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:40:06 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/02 19:54:07 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

// void	fin_lop(t_fd_ *fd_in_out, int i, t_status **status)
// {
// 	wit_process(i, &fd_in_out->pids, fd_in_out, status);
// 	close_file(fd_in_out, fd_in_out->fd);
// }

// static t_fd_	*init_and_create_cmd(t_cmd **lst_cmd, t_env **env, char *line,
// 		t_status **status)
// {
// 	t_fd_	*fd_in_out;

// 	fd_in_out = NULL;
// 	fd_in_out = ft_calloc(1, sizeof(t_fd_));
// 	fd_in_out->stdin = 0;
// 	fd_in_out->stdout = 0;
// 	fd_in_out->her_doc = -2;
// 	fd_in_out->env = *env;
// 	fd_in_out->envp = get_erray_env(*env);
// 	creat_cmd(lst_cmd, line, fd_in_out->envp, status);
// 	if (!lst_cmd)
// 	{
// 		(*status)->status = 1;
// 		return (NULL);
// 	}
// 	fd_in_out->fd_in = dup(STDIN_FILENO);
// 	fd_in_out->fd_out = dup(STDOUT_FILENO);
// 	fd_in_out->retu_red = 0;
// 	fd_in_out->last = lstlast(*lst_cmd);
// 	return (fd_in_out);
// }

// void	loo_commande(t_cmd *lst_cmd, t_fd_ **fd_in_out, t_status **status)
// {
// 	int		i;
// 		(void)status;
// 	i = 0;
// 	(*fd_in_out)->pids = ft_calloc(lstsize(lst_cmd), sizeof(pid_t));
// 	while (lst_cmd)
// 	{
// 		whillop(&lst_cmd, *fd_in_out, status, &i);
// 		if ((*fd_in_out)->her_doc != -2)
// 			close((*fd_in_out)->her_doc);
// 		lst_cmd = lst_cmd->next;
// 	}
// 	fin_lop(*fd_in_out, i, status);
// 	free_string_array((*fd_in_out)->envp);
// 	free(*fd_in_out);
// 	lstclear(&lst_cmd);
// }

// static void	lop(t_env **env, char *line, t_status **status)
// {
// 	t_fd_	*fd_in_out;
// 	t_cmd	*lst_cmd;
// 	lst_cmd = NULL;
// 	if (!line || !line || ft_strlen(line) == 0)
// 		return ;
// 	fd_in_out = init_and_create_cmd(&lst_cmd, env, line, status);
// 	if (!fd_in_out || !lst_cmd)
// 		return ;
// 	if (fd_in_out && lst_cmd && chek_her_doc(lst_cmd, &fd_in_out, status) == 2)
// 	{
// 		close_file(fd_in_out, fd_in_out->fd);
// 		lstclear(&lst_cmd);
// 		free_string_array(fd_in_out->envp);
// 		return ;
// 	}
// 	if (lstsize(lst_cmd) == 1)
// 	{
// 		if (builting(lst_cmd, env, status, &fd_in_out) == 1)
// 		{
// 			dup2(fd_in_out->fd_in, STDIN_FILENO);
// 			dup2 (fd_in_out->fd_out, STDOUT_FILENO);
// 			close_file(fd_in_out, fd_in_out->fd);
// 			lstclear(&lst_cmd);
// 			free_string_array(fd_in_out->envp);
// 			return ;
// 		}
// 	}
// 	loo_commande(lst_cmd, &fd_in_out, status);
// 		system("leaks minishell");
// }
void leaks(void)
{
	system("leaks minishell");
}
int	main(int argc, char *argv[], char **envp)
{
	char		*line;
	t_env		*envp_new;
	t_status	*status;
	t_env		*tmp;
	t_env		*next;
	t_cmd	*lst_cmd;
	(void)argv;

	if (argc != 1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	envp_new = NULL;
	status = NULL;
	atexit (leaks);
	envp_new = get_env(envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	status = ft_calloc(1, sizeof(t_status));
	while (1)
	{
		line = readline("minishell ");
		if (line == NULL)
			break ;
		add_history(line);
		lst_cmd =  ft_calloc(1, sizeof(t_cmd));
		creat_cmd(&lst_cmd, line, envp, &status);
		free(line);
		line = NULL;
		lstclear(&lst_cmd);
	}
	tmp = envp_new;
	while (tmp)
	{
		free(tmp->key);
		free(tmp->value);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(tmp);
	free(status);
}

