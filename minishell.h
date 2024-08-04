/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:27:31 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/04 19:46:21 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>  // Moved up
# include "getNextLine/get_next_line_bonus.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			**option;
	char			**rederaction;
	char			**fil_name;
	char			**extra_arg;
	int				index;
	int				single;
	int				double_q;
	struct s_cmd	*next;
	int				op;
	int				re;
	int				fi;
	int				ex;
}					t_cmd;

typedef struct s_fd_last
{
	t_env			*env;
	int				fd_in;
	int				fd_out;
	int				stdin;
	int				fd0;
	int				fd1;
	int				stdout;
	int				her_doc;
	int				retu_red;
	pid_t			*pids;
	char			**envp;
	t_cmd			*last;
	int				fd[2];
	int				out;
	int				in;
}					t_fd_;

typedef enum s_TokenType
{
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	WORD,
	SPACE_c,
	IN,
	OUT,
	APPEND,
	HER_DOC,
	CMD,
	VARIABLE,
	OPTION,
	PIP,
	FILE_IN,
	LIM,
	FILE_OUT,
	WILDCARD,
	ERRRO
}					t_TokenType;

typedef struct s_Token
{
	t_TokenType		type;
	char			*value;
}					t_Token;
typedef struct s_status
{
	int				status;
}					t_status;
char				*replace_dollar_question_with_num(char *str, int num);
void				chke_arg(int argc);
int					chek_builting(t_cmd *lst_cmd, t_env **env,
						t_status **status, t_fd_ **fd_in_out);
void				hand_double_qot(t_Token **tokens, int i, char **envp,
						t_status **status);
void				handl_cmd(t_Token **tokens, int i);
void				handl_option(int *i, t_Token *tokens, t_cmd **new);
char				**list_directory(char *path, int *count);
char				*splite(char *str);
char				**exe_wildcard(char *argv);
int					search_match(char *filename, char *pattern);
char				**store_matches(char **entries, char *argv, int count);
char				*remove_cardt(char *str);
int					chek_point(char *str);
char				**resizer(char **entries, int *capacity, int size);
void				free_env(t_env **envp_new);
void				initialise_noud(t_cmd **new, int cp);
int					add_to_noud(t_Token *tokens, int *i, t_cmd **new,
						int num_tokens);
int					chek_syntax_error(t_Token *tokens, t_status **status,
						int num_tokens);
void				add_back_principal(t_cmd **lst, t_cmd *new);
int					size_(t_env *lst);
void				chek_child_processus(char *lim, int fd);
t_env				*seenv_t(char *str);
char				*set_name(char *str);
char				*set_value(char *str);
void				add_exp(t_env *env, char *value, char *var);
void				error_export(t_status **status, char *str);
char				*get_valus(t_env *envs, char *srch);
int					cmd_pwd(char **str, t_status **status);
void				free_string_array(char **array);
int					lstsize(t_cmd *lst);
int					cmd_pwd(char **str, t_status **status);
void				handle_sigint_herdoc(int sigt);
int					whillop(t_cmd **lst_cmd, t_fd_ *fd_in_out,
						t_status **status, int *i);
int					chek_her_doc(t_cmd *lst_cmd, t_fd_ **fd_in_out,
						t_status **status);
int					cheke_dolar(char *str);
char				*remouve_single_double_qout(char *str);
char				*sqipt_whil_cart(char *str);
int					cmd_exit(char **optin, t_status **status);
void				condition(char **p, t_Token **tokens, int *num_tokens,
						int *max_tokens);
char				**exe_wildcard(char *argv);
char				**create_cmmmand(char **str);
void				parent_prossuce(int *fd, t_fd_ **fd_in_out, int i,
						int ret_buil);
void				hand_error(t_status **status, char *str);
void				update_env(t_env **env, char *var, char *value);
void				whilloop(int *fd);
void				wit_process(int nb_prossuce, pid_t **pids, t_fd_ *fd_in_out,
						t_status **status);
void				errer_cmd(char *str, char *ms_err);
int					st_2derra(char **str, int k);
int					strle_2derra(char **str);
char				**realloc_array(char ***str, int capacity);
void				clo(int fd);
int					while_loop(char *lim, t_fd_ **fd_in_out, t_status **status);
int					rediraction(t_cmd *lst_cmd, t_fd_ **fd_in_out,
						t_status **status);
int					builting(t_cmd *lst_cmd, t_env **env, t_status **status,
						t_fd_ **fd_in_out);
void				builting_fork(t_cmd *lst_cmd, t_env **env,
						t_status **status, t_fd_ *fd_in_out);
int					chke_builting(char *str);
void				cmd_unset(t_env **env, char *var);
int					cmd_echo(char **args, t_status **status, t_cmd *lst_cmd);
int					print_env(t_env *env);
int					cmd_export(t_env **env, char **add, t_status **status);
t_env				*get_env(char **envp);
int					cmd_cd(char **path, t_env **env, t_status **status);
char				**get_erray_env(t_env *env);
t_Token				*tokenize(char *p, int *num_tokens);
void				parse(t_Token **tokens, int num_tokens, char **envp,
						t_status **status);
void				error_ch(char *str);
void				filecommade(t_cmd *cmd, char **env);
char				*get_path(char **envp, char *cmd, int i);
t_Token				*realloc_cmd(t_Token **tokens, int *capacity);
void				out(char **p, t_Token **tokens, int *num_tokens);
void				in(char **p, t_Token **tokens, int *num_tokens);
void				word(char **p, t_Token **tokens, int *num_tokens);
void				quot(char **p, t_Token **tokens, int *num_tokens,
						int *max_tokens);
int					is_space(char c);
void				error_alocation(void);
char				*add_valu_variable(char *str, char **envp,
						t_status **status);
char				*remove_single_qoute(char *str);
char				*remove_doubl_qoute(char *str, char **envp,
						t_status **status);
char				*chercher_variable(char *str, char **envp);
void				here_doc(t_cmd *cmd);
void				erro(char *str);
void				exe_cmd(t_cmd *cmd, char **envp);
void				handle_sigint(int sig);
void				child_process(t_cmd *cmd, char **envp, t_fd_ **fd_in_out,
						t_status **status);
void				fin_commande(t_cmd *cmd, char **envp, t_status **status,
						t_fd_ **fd_in_out);
void				close_file(t_fd_ *fd_in_out, int *fd);
void				lstclear(t_cmd **lst);
void				execute(t_cmd *cmd, char **envp);
void				commad_path(t_cmd *cmd, char **envp);
int					lstsize(t_cmd *lst);
t_cmd				*lstlast(t_cmd *lst);
int					chek_herdoc(char *str);
char				*get_path(char **envp, char *cmd, int i);
t_cmd				*creat_cmd(t_cmd **lst, char *command, char **env,
						t_status **status);
char				*strjoi(char *s1, char *s2, char *s3);
char				**split_variable(char *str);
void				error_syntax(char *msg, char *caracter);
void				print_err(t_status **status);
#endif