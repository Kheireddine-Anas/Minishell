#include "minishell.h"

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

static t_cmd	*lstnew(char *command, char **env)
{
	int		i;
	t_cmd	*new;
	int		j;
	char	**command_split;
	int		k;

	j = 0;
	k = 0;
	i = 0;
	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->option = ft_calloc(5,sizeof(char *));
	new->extra_arg = ft_calloc(5,sizeof(char *));
	new->in = NULL;
	new->out = NULL;
	// if(!ft_strchr(command,'\"'))
		command_split = split_and_include_symbols(command);
		// while(command_split)
		// {
		// 	printf("command_split[%d] = %s\n",i,command_split[i]);
		// 	i++;
		
		// }
		// i = 0;
	// else
	// 	command_split = split_singl_qot(command);
	while(command_split[i])
	{
		if(i ==  0 && (get_path(env, command_split[i], 0) || access(command_split[i], X_OK) == 0))
			new->cmd =  ft_strdup(command_split[i]);
		else if(i > 0 && (command_split[i - 1][0] == '>' || command_split[i - 1][0] == '<' || chek_herdoc(command_split[i - 1])))
		{
			new->extra_arg[k] =  ft_strdup(command_split[i]);
			k++;
		}
		else if(command_split[i][0] == '<' || (command_split[i][0] == '<' && command_split[i][1] == '<'))
			new->in =  ft_strdup(command_split[i]);
		else if(command_split[i][0] == '>' || (command_split[i][0] == '>' && command_split[i][1] == '>'))
			new->out = ft_strdup(command_split[i]);
		else 
		{
			new->option[j] = ft_strdup(command_split[i]);
			j++;
		}
		i++;
	}
	new->option[j] = NULL;
	new->extra_arg[k] = NULL;
	new->next = NULL;
	return (new);
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
		new = lstnew(command[i], env);
		new->index = j;
		add_back(lst, new);
		i++;
		j++;
	}
}