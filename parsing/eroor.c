#include "../minishell.h"

void error_alocation(void)
{
	perror("Allocation error");
	exit(EXIT_FAILURE);
}
void errer_cmd( t_status **status, char *str)
{
    (*status)->status = 127;
    ft_putstr_fd("\033[31mminishell: ", 2); 
    ft_putstr_fd(str, 2);
    ft_putstr_fd("\033[0m", 2);
    ft_putstr_fd("\033[31m", 2); 
    perror(" ");
    ft_putstr_fd("\033[0m", 2);
}
void error_ch( t_status **status, char *str)
{
    (*status)->status = 1;
	ft_putstr_fd("\033[34mminishell: ", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd("\033[0m", 2);
    ft_putstr_fd("\033[34m", 2);
    perror(" ");
    ft_putstr_fd("\033[0m", 2);
}

void	erro(t_status **status, char *str)
{
    (*status)->status = 3;
    ft_putstr_fd("\033[33mminishell: ", 2); 
    ft_putstr_fd(str, 2);
    ft_putstr_fd("\033[0m", 2);
    ft_putstr_fd("\033[33m", 2);
    perror(" ");
    ft_putstr_fd("\033[0m", 2);
}

int error_rederaction(t_cmd *cmd)
{
     if(!cmd->option[0] && cmd->in && cmd->in[0] && ft_strcmp("<<", cmd->in[0]) != 0)
     {
        return(1);
     }
    if(!cmd->option[0] && cmd->out && cmd->out[0] &&  ft_strcmp("<<", cmd->in[0]) != 0)
    {
        return(1);
    }
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
        errer_cmd(status, cmd->option[0]);
        return (1);
    }
    if (cmd->option[0] && cmd->option[0] && cmd->option[0][0] == '/')
    {
        if(access(cmd->option[0], X_OK) != 0)
        {
            errer_cmd(status, cmd->option[0]);
            return (1);
        }
    }
    if (cmd->option[0] && cmd->option[0] && cmd->option[0][0] == '.' && cmd->option[0][1] == '/')
    {
        if(access(cmd->option[0], X_OK))
        {
            errer_cmd(status, cmd->option[0]);
            return (1);
        }
		return (0);
    }
    if (cmd->option[0] && !get_path(env,cmd->option[0],0))
    {
        errer_cmd( status, cmd->option[0]);
        return (1);
    }
    return (0);
}
void print_minishell(void)
{
    char* shell_art = 
    "  _____ _          _ _ \n"
    " / ____| |        | | |\n"
    "| (___ | |__   ___| | |\n"
    " \\___ \\| '_ \\ / _ \\ | |\n"
    " ____) | | | |  __/ | |\n"
    "|_____/|_| |_|\\___|_|_|\n";

    ft_putstr_fd("\033[34m", 2);  // Start blue text
    ft_putstr_fd(shell_art, 2);
    ft_putstr_fd("\033[0m", 2);  // Reset color
}