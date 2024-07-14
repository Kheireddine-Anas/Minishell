#include "../minishell.h"
static env_t	*last_f(env_t *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst-> next;
	return (lst);
}
static int	size_(env_t*lst)
{
	env_t	*help;
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

static void	add_back(env_t **lst, env_t *new)
{
	env_t	*last;

	if (!*lst)
	{
		*lst = new;
	}
	else
	{
		last = last_f(*lst);
		last->next = new;
	}
}


static env_t *get_env_data(char *envp)
{

	env_t *noud;

	noud = NULL;
	if(!envp)
		return (NULL);
	noud = malloc(sizeof(env_t));
	if (noud == NULL)
		return (NULL);
	else
	{
		noud->value = ft_strdup(ft_strchr(envp, '=') + 1);
		noud->key = ft_substr(envp, 0, ft_strlen(envp) - ft_strlen(noud->value) - 1);
		noud -> next = NULL;
	}
	return (noud);
}

env_t *get_env(char **envp)
{
    int		i;
    env_t	*env;

	env = NULL;
    i = 0;
    if(!envp)
        return (NULL);
    while (envp[i])
    {
        add_back(&env, get_env_data(envp[i]));
        i++;
    }
    return (env);
}

char **get_erray_env(env_t	*env)
{
	int i;
	char **env_arr;
	int len;

	if(!env)
		return (NULL);
	i = 0;
	len = size_(env);
	env_arr = malloc(sizeof(char *) * (len + 1));
	if (!env_arr)
		return (NULL);
	env_arr[len] = NULL;
	while (env)
	{
		env_arr[i] = strjoi(env->key,"=" ,env->value);
		env = env->next;
		i++;
	}
	return (env_arr);
}

void print_env(env_t *env)
{
	env_t *tmp; 

	tmp = env;
	while (tmp)
	{
		if(ft_strlen(tmp->value) != 0)
			printf("%s=%s\n",tmp->key,tmp->value);
		tmp =tmp->next;
	}
}