/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuang2 <hhuang2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:00:03 by kexu              #+#    #+#             */
/*   Updated: 2026/06/20 16:36:02 by hhuang2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_AND,
	T_OR,
	T_L_PAREN,
	T_R_PAREN,
	T_LESS,
	T_GREAT,
	T_DGREAT,
	T_DLESS
}					t_token_type;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	QUOTE_MIXED
}					t_quote_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_quote_type	quote;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}					t_node_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}					t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	t_quote_type	quoted;
	int				ambiguous;
	int				fd;
	struct s_redir	*next;
}					t_redir;

typedef struct s_arg
{
	char			*value;
	t_quote_type	quote;
	struct s_arg	*next;
}					t_arg;

typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	t_arg			*args;
	t_redir			*redirs;
}					t_ast;

typedef struct s_exec_args
{
	char	*path;
	char	**argv;
	char	**envp;
}			t_exec_args;

typedef struct s_shell
{
	t_env	*env;
	t_ast	*node;
	t_token	*tokens;
	int		last_status;
	int		main;
}			t_shell;

typedef struct s_pipes
{
	int				num_cmd;
	t_ast			**cmds;
	int				**fds;
	pid_t			*pids;
	t_shell			*shell;
}					t_pipes;


extern volatile sig_atomic_t	g_signal;

t_token				*lexer(char *input);
t_ast				*parser(t_token *tokens);
void				expand_ast(t_ast *node, char **envp);
t_arg				*expand_args(t_arg *args, char **envp);
void				expand_redirs(t_redir *redirs, char **envp);
int					has_quotes(char *value);
void				free_words(char **words);
void				free_arg_list(t_arg *args);
int					has_blank(char *value);
int					count_words(char **words);
void				free_ast(t_ast *node);
void				free_tokens(t_token *tokens);

t_ast				*new_ast_node(t_node_type type);
int					token_is_redir(t_token_type type);
t_arg				*append_arg(t_arg *args, char *value, t_quote_type quote);
t_redir				*new_redir(t_redir_type type, char *file,
						t_quote_type quoted);
void				append_redir(t_redir **list, t_redir *new_redir);
t_redir_type		redir_type_from_token(t_token_type type);
t_redir				*parse_redir(t_token **cur);
int					command_has_content(t_ast *cmd);
t_ast				*free_command(t_ast *cmd);
char				*ast_word_value(t_token *token);
int					append_word_to_cmd(t_ast *cmd, t_token **cur);
int					append_redir_to_cmd(t_ast *cmd, t_token **cur);
t_ast				*parse_command(t_token **cur);
t_ast				*parse_primary(t_token **cur);
t_ast				*parse_subshell(t_token **cur);
t_ast				*parse_pipeline(t_token **cur);
t_ast				*parse_logical(t_token **cur);
t_ast				*free_one_ast(t_ast *node);
t_ast				*free_two_ast(t_ast *left, t_ast *right);
int					check_syntax(t_token *tokens);
int					syntax_is_binary_op(t_token_type type);
int					syntax_is_cmd_start(t_token_type type);
char				*syntax_token(t_token *token);
int					print_unexpected(t_token *token);
int					check_redir_target(t_token *token);

/* Init and clean up shell struct */
int					init_shell(t_shell *shell, char **envp);
void    			cleanup_shell(t_shell *shell);
void    			set_shell_status(t_shell *shell, int status);
int 				get_shell_status(t_shell *shell);

/* Init env */
void    			free_env(t_env **env);
t_env				*create_env(char *str, t_env **new);
t_env				*build_env(char **envp);

/* Execve path */
char				*get_env_val(t_env *env, char *key);
char				**get_val_list(t_env *env, char *key);
char				*build_path(char *exec, t_env *env);
char				*final_path(char *exec, t_env *env);

/* Convert env into envp array */
size_t				count_env(t_env *env);
char    			*get_single_str(t_env *env);
char    			**generate_tab(t_env *env);

/* Heredoc */
int 				prepare_heredoc(t_ast *node);
int					handle_redirs(t_redir *redirs);

int					wait_status_code(int status);

/* Convert node into argv list */
int					count_args(t_arg *args);
char				**args_list(t_arg *args);

/* Echo pwd and env commands */
int					has_n_option(char *str);
int					exec_echo(t_ast *node);
int					exec_pwd(void);
int					exec_env(t_shell *shell);

/* Unset */
int					is_valid_key(char *str);
void				delete_env_var(t_env **env, char *str);
int					exec_unset(t_shell *shell, t_ast *node);

/* Exit */
void    			exit_free(char **args, t_shell *shell);
int  				is_numeric(char *str);
int  				ft_atol(char *str, long long *nb);
void    			exit_numeric_msg(char **args, t_shell *shell);
void    			exit_many_args(char **args, t_shell *shell);
int 				exec_exit(t_ast *node, t_shell *shell);

/* Cd */
char    			*cd_path(t_ast *node, t_env **env);
int 				exec_cd(t_ast *node, t_env **env);

/* Export */
t_env   			*last_env_node(t_env *env);
void    			append_new_node(t_env **env, char *key, char *val);
void				set_env_val(t_env **env, char *key, char *val);
char 				*extract_key(char *str);
char    			*extract_value(char *str);
int 				extract_export(t_arg *arg, t_env **env);
int					exec_export(t_ast *node, t_env **env);

/* Execute cmd */
int					exec_builtin(char *exec, t_ast *node, t_shell *shell);
int					builtin_process(char *exec, t_ast *node, t_shell *shell);
int					is_builtin(char *cmd);
int					exec_cmd_parent(char *exec, t_ast *node, t_shell *shell);
int					execute_cmd(t_ast *node, t_shell *shell, int pipe);

/* Execute child process */
int					path_error_status(char *exec);
int					wait_status_code(pid_t pid);
void				exec_child(char *exec, char *path, char **argv, char **envp);
int					exec_external(char *exec, t_ast *node, t_shell *shell, int pipe);
int					external_process(char *exec, t_ast *node, t_shell *shell, int pipe);

/* Bonus */
int					execute_and(t_ast *node, t_shell *shell);
int					execute_or(t_ast *node, t_shell *shell);
int					execute_subshell(t_ast *node, t_env **env);
int					execute_ast(t_ast *node, t_shell *shell, int pipe);

/* Pipes */
int					count_cmds(t_ast *node);
void    			free_fds(int **fds, int count);
int					**generate_pipes(int pipes);
t_pipes 			*init_pipeline(t_ast *node);
void				collect_cmds(t_ast *node, t_ast **cmds, int *i);
int					generate_fork(t_pipes *p);
int					execute_pipe_child(t_pipes *p, int idx);
void				close_all_fds(t_pipes *p);
void				free_pipeline(t_pipes *p);
int					wait_pipe_status(t_pipes *p);
int					execute_pipe(t_ast *node, t_shell *shell);

void				print_ast(t_ast *node, int level);
void				print_tokens(t_token *tokens);
void				print_ast_node(t_ast *node, char *prefix,
						int last, int *id);
void				print_ast_args(t_arg *args, char *prefix, int last);
void				print_ast_redirs(t_redir *redirs, char *prefix,
						int last);
char				*debug_node_name(t_node_type type);
char				*debug_redir_name(t_redir_type type);
char				*debug_quote_name(t_quote_type quote);
char				*debug_branch(int last);
void				debug_next_prefix(char *dst, char *src, int last);
void				setup_interactive_signals(void);
void				setup_child_signals(void);
void				configure_terminal(void);
void				setup_parent_wait_signals(void);

t_token				*new_token(t_token_type type, char *value);
void				append_token(t_token **list, t_token *new_token);
t_token				*read_word_token(char *input, int *i);
int					is_word_delim(char c);
t_quote_type		word_quote_type(char *word);
t_token				*finish_word_token(char *word);
char				*expand_value(char *value, char **envp);
int					is_var_char(char c);
char				*lookup_value(char *name, char **envp);
char				*expand_name(char *value, int *i, char **envp);
char				*strip_quotes(char *value);
int					has_unquoted_star(char *value);
char				**expand_wildcard(char *pattern);
char				**append_match(char **matches, char *value);
void				sort_matches(char **matches);
int					get_last_status(void);
void				set_last_status(int status);

#endif
