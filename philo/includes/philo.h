/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaufil <cbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:02:11 by acabon            #+#    #+#             */
/*   Updated: 2025/02/04 17:24:58 by cbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/gc_manager.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# define ENV 0
# define PROMPT "minishell:~$ "
# define FLAGS "\x00\'\""
# define UNCLOSED_QUOTE 0xffffffffffffffff
# define NO_ERROR -1
# define READ 0
# define WRITE 1
# define STOP_HEREDOC 0xffffffffffffffff

extern volatile sig_atomic_t	g_signal_received;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_builtins		t_builtins;
typedef struct s_global
{
	t_env		*env;
	t_builtins	**builtins;
	int			last_ret;
	int			current_pipe;
}	t_global;

typedef int						(*t_func)(char **argv, t_global *global);

typedef struct s_builtins
{
	char		*name;
	t_func		func;
}	t_builtins;

typedef struct s_command
{
	char				*name;
	char				**params;
	int					in;
	int					out;
	struct s_command	*next;
}	t_command;

// to delete
enum	e_flag_value
{
	NO_QUOTE,
	SIMPLE_QUOTE,
	DOUBLE_QUOTE,
};

enum	e_limiters
{
	NOT_LIMITER,
	PIPE,
	SINGLE_OUT,
	DOUBLE_OUT,
	SINGLE_IN,
	DOUBLE_IN,
};

enum	e_word
{
	INFILE = 6,
	OUTFILE,
	OUTFILE_APPEND,
	HERE_DOC_WORD,
	COMMAND,
	ARGS,
};

// FLAG:

// 0 = simple
// 1 = simple quoted string
// 2 = double quoted string
typedef struct s_token
{
	char			*value;
	struct s_token	*next;
	int				limiter;
	t_env			*env;
}	t_token;

typedef struct s_final_token
{
	struct s_final_token	*next;
	int						limiter;
	char					**args;
}	t_final_token;

// Env managment
t_env		*init_env(char **envp);
t_env		*find_node(t_env *env, char *key);
int			unset_exec(char *key, t_env **begin);
t_env		*push_env(t_env **begin, char *pair);
t_env		*push_env_from_pairs(t_env **begin, char *key, char *value);
t_env		*create_env_node(char *pair);
void		free_env_node(t_env *node);
char		*split_key(char *pair);
char		*split_value(char *pair);
int			*get_exit_code(void);

// Builtins
int			blt_unset(char **argv, t_global *global);
int			blt_export(char **argv, t_global *global);

int			blt_exit(char **argv, t_global *global);
int			blt_echo(char **argv, t_global *global);
int			blt_pwd(char **argv, t_global *global);
int			blt_cd(char **argv, t_global *global);
int			blt_env(char **argv, t_global *global);
void		exec_env(t_env *node, int flag);
t_func		get_builtin(char *name, t_builtins **cmds);
int			blt_execve(char *pathname, char **argv, t_global *global);

// Init
t_global	init_global(char **envp);
t_builtins	**init_builtins(void);

// cmd managment
t_builtins	*is_builtin(t_builtins **cmds, char *str);

// test parsing
t_token		*push_node(t_token *node, t_token **begin);
t_token		*insert_node(t_token *node, t_token *target);
t_token		**delete_node_token(t_token *node_deleted, t_token **begin);
int			splitting_tokens(t_token **begin);
t_token		*create_token_node(char *value);
t_token		*extract_quotes(char *input);
int			is_quote(char c);
int			replace_var(t_token *begin, t_env *env);
int			replace_exit(t_token *token);
void		set_limiters(t_token *begin);
void		set_redirections(t_token *begin);
t_command	*create_cmd_node(void);
t_command	*push_cmd_node(t_command *new_node, t_command **begin);
t_command	**delete_node_cmd(t_command *node_deleted, t_command **begin);
t_command	*token_to_cmd(t_token *begin_token);
t_command	*get_pipeline(char *line, t_global *global);
int			nb_cmds(t_command *begin_list);
t_command	*get_cmd(t_command *begin_list, int nb);
char		*var_to_str(char *str, t_env *env);
void		error_fd(t_command **begin_cmd, t_token **begin_token,
				t_command **new_cmd, int *current_arg);
void		identify_token(t_command **begin_cmd, t_token **current_token,
				t_command **new_cmd, int *current_arg);
// Parsing errors
t_bool		unclosed_quotes(char *input);
int			get_error_type(t_token *token, t_token *prev);
int			check_syntax_errors(t_token	*begin);

// Executing
void		*minishell_routine(char *line, t_global *global);
int			get_input(char *path, int limiter, t_env *env);
char		**envp_to_array(t_env *begin);
char		*get_here_doc(char *limiter, t_env *env);
int			alone_builtin_exec(t_global *global, t_command *pipeline);
int			fork_and_pipe(t_global *global, t_command *cmds);
int			exec(t_command *cmd, t_global *global);
int			(*init_pipes(t_command *cmds, size_t *nbr_cmds))[2];
void		redirect_output(t_command *current, size_t i,
				size_t nbr_cmds, int (*pipes)[2]);
void		redirect_input(t_command *current, size_t i, int (*pipes)[2]);
void		close_pipes(int (*pipes)[2], size_t nbr_cmds);
// Signals
void		main_handle_sigint(void);
void		main_handle_sigquit(void);
void		sigint_here_doc_handler(int signal);
void		handle_signals(void);
// to remove !!
void		debug_putlist(t_token *begin_list);
void		debug_putcmd(t_command *begin_list);

#endif