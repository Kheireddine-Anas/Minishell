#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
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

char	*ft_join(char *s1, char *s2, int val)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (0);
	while (i[s1])
	{
		str[i] = s1[i];
		i++;
	}
	if (val)
		str[i++] = '=';
	else
		str[i++] = '/';
	while (*s2)
		str[i++] = *s2++;
	str[i] = 0;
	if (!val)
		free(s1);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strstr(char *str, char *to_find)
{
	unsigned int	cc;
	unsigned int	i;

	if (!*to_find)
		return ((char*)str);
	cc = 0;
	while (str[cc] != '\0')
	{
		if (str[cc] == to_find[0])
		{
			i = 1;
			while (to_find[i] != '\0' && str[cc + i] == to_find[i])
				++i;
			if (to_find[i] == '\0')
				return ((char*)&str[cc]);
		}
		++cc;
	}
	return (0);
}

static int	nb_len(int n)
{
	int	len;

	len = 0;
	if (n < 1)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	nbr;

	len = nb_len(n);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	*(str + len) = '\0';
	nbr = n;
	if (n < 0)
		nbr = -n;
	while (len--)
	{
		*(str + len) = 48 + nbr % 10;
		nbr /= 10;
	}
	if (n < 0)
		*(str) = '-';
	return (str);
}

char	*allocator(char *str, char cc, int start, int lenght)
{
	char	*all;
	int		i;

	all = (char *)malloc(lenght + 1);
	i = start;
	lenght = 0;
	while (str[i])
	{
		if ((str[i] == cc && str[i + 1] == cc)
			|| (str[i] == cc && str[i + 1] == '\0'))
			i++;
		else
			all[lenght++] = str[i++];
	}
	all[lenght] = '\0';
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (all);
}

char	*strtrim_mine(char *str, char cc)
{
	int		i;
	int		lenght;
	int		start;
	char	*all;

	i = 0;
	lenght = 0;
	while (str[i] == cc)
		i++;
	start = i;
	while (str[i])
	{
		if ((str[i] == cc && str[i + 1] == cc)
			|| (str[i] == cc && str[i + 1] == '\0'))
			i++;
		else
		{
			lenght++;
			i++;
		}
	}
	all = allocator(str, cc, start, lenght);
	return (all);
}

char	*ft_strjoin(char *str, char *str1)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	tmp = ft_calloc(ft_strlen(str) + ft_strlen(str1) + 1, sizeof(char));
	while (str && str[++i])
		tmp[i] = str[i];
	if (str)
		free(str);
	while (str1 && str1[j])
		tmp[i++] = str1[j++];
	tmp[i] = '\0';
	return (tmp);
}