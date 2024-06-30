#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(int count, int size)
{
	char	*hld;
	int		i;

	hld = malloc(count * size);
	i = 0;
	if (!hld)
		exit(1);
	while (i < (count * size))
	{
		hld[i] = 0;
		i++;
	}
	return (hld);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((s1[i] != s2[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*get_env(t_env *envs, char *srch)
{
	t_env	*tmp;

	tmp = envs;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->variable, srch)))
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_strdup(char *s)
{
	char	*dst;
	int		i;

	i = 0;
	dst = (char *)malloc(ft_strlen(s) + 1);
	if (!dst)
			return (NULL);
	while (s[i])
	{
			dst[i] = s[i];
			i++;
	}
	dst[i] = '\0';
	return (dst);
}