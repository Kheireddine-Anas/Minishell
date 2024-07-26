i = 0;
	if (lst_cmd->fil_out[i])
	{
		i = 0;
		while (lst_cmd->fil_out[i])
		{
			if (i < (strle_2derra(lst_cmd->fil_out) - 1))
			{
				fd[i] = open(lst_cmd->fil_out[i], O_CREAT | O_WRONLY | O_TRUNC,
						0777);
				if ((*fd_in_out)->stdout == -1)
				{
					(*status)->status = 3;
					erro(lst_cmd->fil_out[i]);
					return (2);
				}
				close(fd[i]);
			}
			i++;
		}
		i--;
		if (ft_strcmp(">", lst_cmd->out[i]) == 0)
			(*fd_in_out)->stdout = open(lst_cmd->fil_out[i],
					O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (ft_strcmp(">>", lst_cmd->out[i]) == 0)
			(*fd_in_out)->stdout = open(lst_cmd->fil_out[i],
					O_CREAT | O_RDWR | O_APPEND, 0777);
		if ((*fd_in_out)->stdout == -1)
		{
			(*status)->status = 3;
			erro(lst_cmd->fil_out[i]);
			return (2);
		}
		dup2((*fd_in_out)->stdout, STDOUT_FILENO);
		return (3);
	}