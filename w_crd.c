#include "crd.h"

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

char	**list_directory(const char *path, int *count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**entries;
	char			**new_entries;
	int				capacity;
	int				new_capacity;
	int				size;
	int				i;

	dir = opendir(path);
	if (!dir)
		perror("opendir problem");
	capacity = 10;
	size = 0;
	i = 0;
	entries = ft_calloc(capacity, sizeof(char *)); //Protect the allocation
	while ((entry = readdir(dir)) != NULL)
	{
		if (size >= capacity)
		{
			new_capacity = capacity * 2;
			new_entries = ft_calloc(new_capacity, sizeof(char *)); //Protect the allocation
			while (i < size)
			{
				new_entries[i] = entries[i];
				i++;
			}
			free(entries);
			entries = new_entries;
			capacity = new_capacity;
		}
		entries[size] = ft_strdup(entry->d_name); //Protect the allocation
		size++;
	}
	closedir(dir);
	*count = size;
	return (entries);
}

int	match_pattern(const char *filename, const char *pattern)
{
	if (pattern[0] == '*' && pattern[strlen(pattern) - 1] == '*')
		return (strstr(filename, pattern + 1) != NULL);
	if (pattern[0] == '*')
		return (strstr(filename, pattern + 1) ==
			filename + strlen(filename) - strlen(pattern) + 1);
	if (pattern[strlen(pattern) - 1] == '*')
		return (strncmp(filename, pattern, strlen(pattern) - 1) == 0);
	return (strcmp(filename, pattern) == 0);
}

void	exe_wildcard(char *argv[])
{
	int		count;
	char	**entries;
	int		i;
	int		j;

	entries = list_directory(".", &count);
	i = 0;
	while (entries[i])
	{
		printf(">%s\n", entries[i++]); // Just to show the entries
	}
	i = 1;
	while (argv[i])
	{
		if (strchr(argv[i], '*'))
		{
			while (j < count)
			{
				if (match_pattern(entries[j], argv[i]))
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

void	handle_command(int argc, char *argv[])
{
	if (argc > 1)
	{
		exe_wildcard(argv);
	}
	else
	{
		printf("Usage: <command> <arguments>\n");
	}
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: <command> <arguments>\n");
		return (1);
	}
	handle_command(argc, argv);
	return (0);
}
