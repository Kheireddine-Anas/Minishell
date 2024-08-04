#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to create a new trimmed string
char	*ft_new(char *str, char sep, int start, int j)
{
	char	*new;
	int		i;

	new = (char *)malloc(j + 1);
	i = start;
	j = 0;
	while (str[i])
	{
		if ((str[i] == sep && str[i + 1] == sep)
			|| (str[i] == sep && str[i + 1] == '\0'))
			i++;
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	if (str)
	{
		// free(str);
		str = NULL;
	}
	return (new);
}

char	*ft_trim(char *str, char sep)
{
	int		i;
	int		j;
	int		start;
	char	*new;

	i = 0;
	j = 0;
	while (str[i] == sep)
		i++;
	start = i;
	while (str[i])
	{
		if ((str[i] == sep && str[i + 1] == sep)
			|| (str[i] == sep && str[i + 1] == '\0'))
			i++;
		else
		{
			j++;
			i++;
		}
	}
	new = ft_new(str, sep, start, j);
	return (new);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (start >= strlen(s))
		return (strdup(""));
	if (strlen(s) - start > len)
		str = (char *)malloc(len + 1);
	else
		str = (char *)malloc(strlen(s) - start + 1);
	if (!str)
		return (NULL);
	while (len-- > 0 && s[start])
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	to_right(const char *str, const char *set)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (str[i] && set[j])
	{
		if (str[i] == j[set])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

static int	str_len(char const *str, char const *set)
{
	int	l_str;
	int	i;

	i = 0;
	l_str = strlen(str) - 1;
	while (set[i] && l_str > 0)
	{
		if (set[i] == str[l_str])
		{
			l_str--;
			i = 0;
		}
		else
			i++;
	}
	return (l_str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	int				start;
	int				l_str;

	str = (char *)s1;
	start = to_right(str, set);
	l_str = str_len(str, set);
	if (!str || !set)
		return (NULL);
	return (ft_substr(str, start, (l_str - start) + 1));
}

int main() {
    char str[] = "		hello  world  ";
    const char *trimmed_str = ft_strtrim(str, " ");
    char *trimmed_str1 = ft_trim(str, ' ');
    if (trimmed_str) {
        printf(": '%s'\n", trimmed_str);
        printf(": '%s'\n", trimmed_str1);
        // free(trimmed_str); // Don't forget to free the allocated memory
    } else {
        printf("Empty or NULL input string.\n");
    }
    return 0;
}
