#include "minishell.h"

char	*ft_strjoi(char *s1, char *s2, char *s3)
{
	int		size_total;
	char	*res;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s1)
		return (ft_strdup(s2));
	size_total = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	res = malloc(size_total + 1);
	if (!res)
		return (NULL);
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		res[i++] = s2[j++];
	j = 0;
	while (s3[j] != '\0')
		res[i++] = s3[j++];
	res[i] = '\0';
	return (res);
}

static int	lstsize(env_t *lst)
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

env_t	*lstlast(env_t *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst-> next;
	return (lst);
}
static void	ft_add_back(env_t **lst, env_t *new)
{
	env_t	*last;

	if (!*lst)
	{
		*lst = new;
	}
	else
	{
		last = lstlast(*lst);
		last->next = new;
	}
}
static env_t *get_env_data(char *envp)
{

	env_t *noud;
	noud = malloc (sizeof(env_t));
	if (noud == NULL)
		return (NULL);
	else
	{
		noud->value = ft_strdup(ft_strchr(envp, '=') + 1);
		noud->key = ft_substr(envp, 0, ft_strlen(envp) - ft_strlen(noud->value) - 1);
		noud -> next = NULL;
	}
	return (noud);
	return (noud);
}

env_t *get_env(char **envp)
{
	int		i;
	env_t	*env;

	i = 0;
	while (envp[i])
	{
		ft_add_back(&env, get_env_data(envp[i]));
		i++;
	}
	return (env);
}

char **get_erray_env(env_t	*env)
{
	int i;
	char **env_arr;
	int len;

	i = 0;
	len = lstsize(env);
	env_arr = malloc(sizeof(char *) * (len + 1));
	if (!env_arr)
		return (NULL);
	env_arr[len] = NULL;
	while (env)
	{
		env_arr[i] = ft_strjoi(env->key,"=" ,env->value);
		env = env->next;
		i++;
	}
	return (env_arr);
}
