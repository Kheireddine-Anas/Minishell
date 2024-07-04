#include "minishell.h"

static void	ft_free(char **result, int j)
{
	while (j > 0)
	{
		j--;
		free(result[j]);
	}
	free(result);
}

static int	ft_count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == '|')
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] && str[i] != '|')
			i++;
	}
	return (count);
}

static char	**ft_alloc_mem(char *s, char **result, int start)
{
	int	i;
	int	len;

	i = 0;
	while (i < ft_count_words(s))
	{
		while (s[start] == '|')
			start++;
		len = 0;
		while (s[start + len] && s[start + len] != '|')
			len++;
		result[i] = ft_calloc((len + 1) , sizeof(char));
		if (!result[i])
		{
			ft_free(result, i);
			return (NULL);
		}
		ft_strlcpy(result[i], &s[start], len + 1);
		start += len;
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split_pipe(char *s)
{
	char	**result;
	int		start;

	if (!s)
		return (NULL);
	start = 0;
	result = ft_calloc((ft_count_words(s) + 1) , sizeof(char *));
	if (result == NULL)
		return (NULL);
	result = ft_alloc_mem(s, result, start);
	return (result);
}
