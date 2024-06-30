
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
		while (is_sep(str[i]))
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] && !is_sep(str[i]))
			i++;
	}
	return (count);
}

static char	**ft_alloc_mem(char *s, char **result, int start)
{
	int	i;
	int	len;

	i = 0;
	while (i <= ft_count_words(s))
	{
		while (is_sep(s[start]))
			start++;
		len = 0;
		while (s[start + len] && (!is_sep(s[start + len])))
			len++;
		result[i] = ft_calloc((len + 1) , sizeof(char));
		if (!result[i])
		{
			ft_free(result, i);
			return (NULL);
		}
		ft_strlcpy(result[i], &s[start], len + 1);
		if(s[start - 1] == '$')
			result[i] = ft_strjoin("$", result[i]);
		start += len;
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**splite_variable(char *s)
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
int ft_strlen_2_erra(char **str)
{
	int i;

	i = 0;
	if(!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}