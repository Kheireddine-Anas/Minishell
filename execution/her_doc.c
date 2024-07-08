#include "../minishell.h"
void	while_loop(t_cmd *cmd, int *fd)
{
	char	*str;
	char	*strj;

	strj = ft_strjoin(*(cmd->extra_arg), "\n");
	cmd->extra_arg++;
	while (1)
	{
		printf("here_doc> ");
		str = get_next_line(STDIN_FILENO);
		if (!str ||!ft_strncmp(strj, str, ft_strlen(str)))
			break ;
		ft_putstr_fd(str, fd[1]);
			free(str);
	}
	free(str);
	free(strj);
}
void here_doc(t_cmd *cmd, int *fd)
{
	char	*str;
	char	*strj;

	strj = ft_strjoin(*(cmd->extra_arg), "\n");
	cmd->extra_arg++;
	while (1)
	{
		str = get_next_line(0);
		if (!str ||!ft_strncmp(strj, str, ft_strlen(str)))
			break ;
		ft_putstr_fd(str, fd[1]);
		free(str);
	}
	free(str);
	free(strj);
}