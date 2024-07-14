#include "../minishell.h"

void error_alocation(void)
{
	perror("Allocation error");
	exit(EXIT_FAILURE);
}
static void errer_cmd( t_status **status)
{
	perror("invalide command ");
	(*status)->status = 127;
	return ;
}
void error_ch( t_status **status)
{
	perror("invalide command ");
	(*status)->status = 1;
}
int error_rederaction(t_cmd *cmd)
{
     if(!cmd->option[0] && cmd->in && cmd->in[0] && ft_strcmp("<<", cmd->in[0]) != 0)
		return(1);
    if(!cmd->option[0] && cmd->out && cmd->out[0] &&  ft_strcmp("<<", cmd->in[0]) != 0)
		return(1);
    if (!cmd->option[0] && cmd->in  && ft_strcmp("<<", cmd->in[0]) == 0)
    {
        here_doc(cmd);
        return (1);
    }
    return (0);
}
int	filecommade(t_cmd *cmd, char **env, t_status **status)
{
    if (!cmd)
		return (1);
   if(error_rederaction(cmd)== 1)
		return (1);
    if (cmd->option && cmd->option[0] && cmd->option[0][0] == '\0')
    {
        errer_cmd(status);
        return (1);
    }
    if (cmd->option[0] && cmd->option[0] && cmd->option[0][0] == '/')
    {
        if(access(cmd->option[0], X_OK) != 0)
        {
            errer_cmd(status);
            return (1);
        }
    }
    if (cmd->option[0] && cmd->option[0] && cmd->option[0][0] == '.' && cmd->option[0][1] == '/')
    {
        if(access(cmd->option[0], X_OK))
        {
            errer_cmd(status);
            return (1);
        }
		return (0);
    }
    if (cmd->option[0] && !get_path(env,cmd->option[0],0))
    {
        errer_cmd( status);
        return (1);
    }
    return (0);
}