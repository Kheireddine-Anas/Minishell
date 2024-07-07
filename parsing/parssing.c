#include "../minishell.h"

void	lstclear(t_cmd **lst)
{
	t_cmd	*help;
	t_cmd	*next;

	if (*lst == NULL)
		return ;
	help = *lst;
	next = NULL;
	while (help != NULL)
	{
		next = help -> next;
		free(help->cmd);
		free(help->in);
		free(help->out);
		free(help->option);
		free(help->extra_arg);
		free (help);
		help = next;
	}
	*lst = NULL;
}

int	lstsize(t_cmd *lst)
{
	t_cmd	*help;
	int		len;

	len = 0;
	help = lst;
	while (help != NULL)
	{
		help = help -> next;
		len++;
	}
	return (len);
}

t_cmd	*lstlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst-> next;
	return (lst);
}
static void	add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (!*lst)
		*lst = new;
	else
	{
		last = lstlast(*lst);
		last->next = new;
	}
}

void creat_cmd(t_cmd	**lst, char **command, char **env)
{
	t_cmd	*new;
	int		i;
	int 	j;

	j = 0;
	i = 0;
	new = NULL;
	while(command[i])
	{
		printf("******\n");
		new = lstnew(command[i], env);
		new->index = j;
		add_back(lst, new);
		i++;
		j++;
	}
}