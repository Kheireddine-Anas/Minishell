#include "w_crd.h"

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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

void	*ft_calloc(int count, int size)
{
	char	*hld;
	int		i;

	hld = malloc(count * size);
	if (!hld)
		exit(1);
	i = 0;
	while (i < count * size)
	{
		hld[i] = 0;
		i++;
	}
	return (hld);
}

char	**resizer(char **entries, int *capacity, int size)
{
	char	**new_entries;
	int		new_capacity;
	int		i;

	new_capacity = *capacity * 2;
	new_entries = ft_calloc(new_capacity, sizeof(char *));
	if (!new_entries)
		perror("ft_calloc");
	i = 0;
	while (i < size)
	{
		new_entries[i] = entries[i];
		i++;
	}
	free(entries);
	*capacity = new_capacity;
	return (new_entries);
}

char	**list_directory(char *path, int *count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**entries;
	int				capacity;
	int				size;

	dir = opendir(path);
	if (!dir)
	{
		perror("opendir problem");
		exit(EXIT_FAILURE);
	}
	capacity = 10;
	size = 0;
	entries = ft_calloc(capacity, sizeof(char *));
	while ((entry = readdir(dir)) != NULL)
	{
		if (size >= capacity)
		{
			entries = resizer(entries, &capacity, size);
		}
		entries[size] = ft_strdup(entry->d_name);
		size++;
	}
	closedir(dir);
	*count = size;
	return (entries);
}

int	search_match(char *filename, char *pattern)
{
	if (pattern[0] == '*' && pattern[ft_strlen(pattern) - 1] == '*')
		return (ft_strstr(filename, pattern + 1) != NULL);
	if (pattern[0] == '*')
		return (ft_strstr(filename, pattern + 1) == filename + ft_strlen(filename) - ft_strlen(pattern) + 1);
	if (pattern[ft_strlen(pattern) - 1] == '*')
		return (strncmp(filename, pattern, ft_strlen(pattern) - 1) == 0);
	return (ft_strcmp(filename, pattern) == 0);
}

void	exe_wildcard(char *argv[])
{
	int		count;
	char	**entries;
	int		i;
	int		j;

	entries = list_directory(".", &count);
	i = 1;
	while (argv[i])
	{
		j = 0;
		if (ft_strchr(argv[i], '*'))
		{
			while (j < count)
			{
				if (search_match(entries[j], argv[i]))
					printf("%s ", entries[j]);
				j++;
			}
		}
		else
			printf("%s ", argv[i]);
		i++;
	}
	printf("\n");
	while (i < count)
		free(entries[i++]);
	free(entries);
}


int main(int argc, char **argv) {
	char	**array;
	int		i;

	array = (char **)malloc((argc - 1) * sizeof(char *));
	if (!array) {
		perror("Memory allocation failed");
		return 1;
	}
	i = 1;
	while (i < argc) {
		array[i - 1] = ft_strdup(argv[i]);
		i++;
	}
	exe_wildcard(array);
	return 0;
}


