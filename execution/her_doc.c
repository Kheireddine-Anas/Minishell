#include "../minishell.h"
int	while_loop(t_cmd **cmd ,t_fd_ **fd_in_out)
{
	char	*str;
	char	*strj;
	int	fd;

	dup2((*fd_in_out)->fd_in,STDIN_FILENO);
	dup2((*fd_in_out)->fd_out,STDOUT_FILENO);
	fd = open("/tmp/her_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if(fd == -1)
	{
		perror("Error in open file");
		return (-2);
	}
	strj = ft_strjoin((*(*cmd)->extra_arg), "\n");
	(*cmd)->extra_arg++;
	while (1)
	{
		ft_putstr_fd("here_doc> ",0);
		str = get_next_line(STDIN_FILENO);
		if (!str ||!ft_strncmp(strj, str, ft_strlen(str)))
			break ;
		ft_putstr_fd(str, fd);
		free(str);
	}
	free(str);
	free(strj);
	return (fd);
}
void here_doc(t_cmd *cmd)
{
    char	*str;
    char	*strj;

    strj = ft_strjoin(*(cmd->extra_arg), "\n");
    cmd->extra_arg++;
    while (1)
    {
		ft_putstr_fd("> ",0);
        str = get_next_line(STDIN_FILENO);
        if (!str ||!ft_strncmp(strj, str, ft_strlen(str)))
        {
            free(str);
            break ;
        }
        free(str);
    }
    free(strj);
}