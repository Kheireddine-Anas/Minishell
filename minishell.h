#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum				s_token
{
	D_QUOTE = '\"',
	S_QUOTE = '\'',
	BK_SL = '\\',
	WSPACE = ' ',
	PIPE = '|',
	VAR = '$',
	OUT = '>',
	IN = '<',
	WORD,
	HERE_DOC,
	OUT_FILE,
} e_token;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct  s_red
{
	/* data */
	e_token type;
	char *file;
	struct s_red *next;

} t_redir;
 
typedef struct s_data
{
	char	**cmnd;
	t_redir *red;
	char **env;
	struct s_data *next;

}	t_data;



typedef struct s_lexer
{
	char			*value;
	e_token	type;
	struct s_lexer	*next;
}	t_lexer;

void	*ft_calloc(int count, int size);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2, int val);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*get_env(t_env *envs, char *srch);
void	cmd_cd(char **path, t_env *env);
char	*set_name(char *str);
char	*set_value(char *str);
char	*cmd_pwd(int val);
t_env	*set_env(char *str);
void	cmd_export(t_env *env, char **add);
void	cmd_unset(t_env **env, char *var);
char	**ft_split(char const *str, char c);

void	ft_print_lexer(t_lexer *lexer);

#endif