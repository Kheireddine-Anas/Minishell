#include "../minishell.h"
int	strle_2derra(char **str)
{
	int i = 0;
	while(str[i])
		i++;
	return (i);
}
int	rediraction(t_cmd	*lst_cmd, t_status **status,  t_fd_ **fd_in_out)
{
	int i = 0;
	int *fd;

	fd = ft_calloc(ft_strlen(*lst_cmd->fil_out), sizeof(int));
	if (lst_cmd->in[i])
	{
		while(lst_cmd->in[i])
		{
			if(ft_strcmp("<<",lst_cmd->in[i]) == 0)
			{
				(*fd_in_out)->her_doc = while_loop(&lst_cmd,fd_in_out);
				if ( (*fd_in_out)->her_doc == -2)
					return (2);
			}	
			if( (i  < strle_2derra(lst_cmd->fil_in) - 1) && ft_strcmp("<<",lst_cmd->in[i]) != 0)
			{
				(*fd_in_out)->STDIN  = open(lst_cmd->fil_in[i], O_RDONLY );
				if ((*fd_in_out)->STDIN == -1)
				{
					erro(status, lst_cmd->fil_in[i]);
					return (2);
				}
				close((*fd_in_out)->STDIN);
			}
			i++;
		}
		i--;
		if(ft_strcmp("<<",lst_cmd->in[i]) == 0)
		{
			close((*fd_in_out)->her_doc);
			(*fd_in_out)->her_doc = open("/tmp/her_doc", O_CREAT | O_RDWR, 0777);
			if((*fd_in_out)->her_doc== -1)
			{
				erro(status, "her_doc");
				return (2);
			}
			dup2((*fd_in_out)->her_doc, STDIN_FILENO);
		}
		else
		{
			(*fd_in_out)->STDIN  = open(lst_cmd->fil_in[i], O_RDONLY );
			if ((*fd_in_out)->STDIN == -1)
			{
				erro(status , lst_cmd->fil_in[i]);
				return (2);
			}
			dup2((*fd_in_out)->STDIN , STDIN_FILENO);
		}
	}
	if (*lst_cmd->fil_out)
	{
		i = 0;
		while(lst_cmd->fil_out[i])
		{
			if( i  < (strle_2derra(lst_cmd->fil_out) - 1))
			{
				fd[i]  = open(lst_cmd->fil_out[i], O_CREAT | O_WRONLY |O_TRUNC, 0777);
				if ((*fd_in_out)->STDOUT  == -1)
				{
					erro(status, lst_cmd->fil_out[i]);
					return (2);
				}
					
				close(fd[i]);
			}
			i++;
		}
		i--;
		if(ft_strcmp(">",lst_cmd->out[i]) == 0)
			(*fd_in_out)->STDOUT = open(lst_cmd->fil_out[i], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if(ft_strcmp(">>",lst_cmd->out[i]) == 0)
    		(*fd_in_out)->STDOUT = open(lst_cmd->fil_out[i], O_CREAT | O_RDWR | O_APPEND, 0777);
		if ((*fd_in_out)->STDOUT  == -1)
		{
			erro(status, lst_cmd->fil_out[i]);
			return (2);
		}
		dup2((*fd_in_out)->STDOUT  , STDOUT_FILENO);
		return (3);
	}
	return (0);
}
int  builting(t_cmd	*lst_cmd, env_t	**env, t_status **status,  t_fd_ **fd_in_out) 
{
	if (lst_cmd ->option && ft_strcmp("cd", lst_cmd->option[0]) == 0)
	{
		cmd_cd(lst_cmd->option, env, status);
		(*status)->status  = 0;
		return(1);
	}
	if (lst_cmd ->option  && lst_cmd ->option && ft_strcmp("env", lst_cmd->option[0]) == 0)
	{
		print_env(*env);
		(*status)->status  = 0;
		return (1);
	}
	if(lst_cmd ->option && ft_strcmp("unset", lst_cmd->option[0]) == 0)
	{
		if (!lst_cmd->option[1])
			return (1);
		cmd_unset(env, lst_cmd->option[1]);
		(*status)->status  = 0;
		return (1);
	}
	if(lst_cmd ->option && ft_strcmp("echo", lst_cmd->option[0]) == 0)
	{
		rediraction(lst_cmd, status, fd_in_out);
		cmd_echo(lst_cmd->option);
		dup2((*fd_in_out)->fd_out , STDOUT_FILENO);
		dup2((*fd_in_out)->fd_in  ,STDIN_FILENO);
		(*status)->status  = 0;
		return (1);
	}
	if(lst_cmd ->option && ft_strcmp("export", lst_cmd->option[0]) == 0)
	{
		cmd_export(env, lst_cmd->option);
		(*status)->status  = 0;
		return (1);
	}
	return (0);
}