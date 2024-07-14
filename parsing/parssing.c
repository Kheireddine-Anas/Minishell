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
		if(help->in)
		{
			while ((*help->in))
			{
				free(*help->in);
				help->in++;
			}
		}
		if(help->out)
			free(help->out);
		if(help->option && *help->option )
			free(help->option);
		if(help->extra_arg && *help->extra_arg)
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
void initialise_noud(t_cmd	**new)
{
	(*new)->single = 0;
	(*new)->double_q = 0;
	(*new)->option = ft_calloc(5,sizeof(char *));
	(*new)->extra_arg = ft_calloc(5,sizeof(char *));
	(*new)->in = ft_calloc(5,sizeof(char *));
	(*new)->fil_in = ft_calloc(5,sizeof(char *));
	(*new)->fil_out = ft_calloc(5,sizeof(char *));
	(*new)->out = ft_calloc(5,sizeof(char *));
}
int  add_to_noud(Token	*tokens, int *i,t_cmd **new , int num_tokens)
{
	int		j;
	int		k;
	int		m;
	int		l;
	int		o;
	int		out;

	j = 0;
	o = 0;
	k = 0;
	l = 0;
	m = 0;
	out = 0;
	(*new) = malloc(sizeof(t_cmd));
	initialise_noud(new);
	while(*i < num_tokens)
	{
		if(tokens[*i].type == PIP)
		{
			(*new)->out[o] = NULL;
			(*new)->extra_arg[m] = NULL;
			(*new)->in[l] = NULL;
			(*new)->option[j] = NULL;
			(*new)->fil_in[k] = NULL;
			(*new)->fil_out[out] = NULL;
			(*new)->next = NULL;
			return(1);
		}
		else if(tokens[*i].type == QUOTE_SINGLE && tokens[*i].value[0] == '\'')
				(*new)->single = 1;
		else if(tokens[*i].type == QUOTE_DOUBLE && tokens[*i].value[0] == '\"')
				(*new)->double_q = 1;
		else if(tokens[*i].type == IN || tokens[*i].type == HER_DOC)
		{
			(*new)->in[l] =  tokens[*i].value;
			l++;
		}
		else if(tokens[*i].type == OUT || tokens[*i].type == APPEND)
		{
			(*new)->out[o] = tokens[*i].value;
			o++;
		}
		else if(tokens[*i].type == OPTION || tokens[*i].type == VARIABLE || tokens[*i].type == QUOTE_SINGLE || tokens[*i].type == QUOTE_DOUBLE || tokens[*i].type == WORD || tokens[*i].type == CMD)
		{
			(*new)->option[j] = tokens[*i].value;
			j++;
		}
		else if(tokens[*i].type == FILE_IN)
		{
			(*new)->fil_in[k] = tokens[*i].value;
			k++;
		}
		else if(tokens[*i].type == FILE_OUT)
		{
			(*new)->fil_out[out] = tokens[*i].value;
			out++;
		}
		else
		{
			(*new)->extra_arg[m] = tokens[*i].value;
			m++;
		}
		*i+=1;
	}
	(*new)->extra_arg[m] = NULL;
	(*new)->out[o] = NULL;
	(*new)->in[l] = NULL;
	(*new)->option[j] = NULL;
	(*new)->fil_in[k] = NULL;
	(*new)->fil_out[out] = NULL;
	(*new)->next = NULL;
	return (0);
}

void creat_cmd(t_cmd	**lst, char *command, char **env, t_status	**status)
{
	int		i;
	t_cmd	*new;
	Token	*tokens;
	int		num_tokens = 0;

	i = 0;
	tokens = tokenize(command, &num_tokens);
	parse(&tokens, num_tokens, env, status);
	while(i < num_tokens)
	{
		if(add_to_noud(tokens, &i, &new, num_tokens) == 1 && i < num_tokens)
		{
			add_back(lst, new);
			new = NULL;
			i++;
		}
		else
			add_back(lst, new);
	}
}