#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# define ERROR_PIPES "Conchita : syntax error near unexpected token `|'"
# define ERROR_NEWLINE "Conchita : syntax error near unexpected token `newline'"
# define ERROR_DOUBLE_QUOTES "Conchita : expected to close the double quote"
# define ERROR_SIMPLE_QUOTES "Conchita : expected to close the quote"
# define ERROR_NO_FILE ": No such file or directory"
# define ERROR_SLASH "Conchita : expected to scape character"

typedef struct s_cmd
{
	char			**argv;
	int				len_argv;
	int				fdin;
	int				fdout;
	int				error;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_tok
{
	struct s_tok	*next;
	char			*content;
	int				type;
	int				flag;
}	t_tok;

typedef struct s_env
{
	struct s_env	*next;
	char			*content;
	char			*name;
}	t_env;

typedef enum e_tok_type
{
	T_PIPE = 1,
	T_HEREDOC = 2,
	T_APPEND = 3,
	T_REDIRECTION_INFILE = 4,
	T_REDIRECTION_OUTFILE = 5,
	T_WORD = 6,
	T_SIMPLE_QUOTE = 7,
	T_DOUBLE_QUOTE = 8,
}	t_tok_type;

typedef struct s_msh
{
	t_cmd	*cmd;
	t_env	*env;
	t_env	*export;
	t_tok	*tok;
	char	*prompt;
	int		len_cmds;
	int		number_status;
	int		number_error;
	int		*pids;
	int		status;
	char	**envp;
}	t_msh;
////////BORRAR*///////
void	init_signal(void);
void	signal_d(t_msh *msh);
void	signal_c(int signal);
void	heredoc_handler(int signum);
///////ENVP////////
void	organization_env(char **envp, t_env **env);
////////FREE///////
void	free_msh(t_msh *msh);
void	free_cmd(t_cmd **cmd);
void	ft_free_node(t_env *node);
void	ft_free_env(t_env **env);
void	ft_kill_children(int *pids, int len);
///////UTILS_PARSER/////////
void	msj_error(char *str, t_msh *msh, int status);
//////UNION TOK//////////
void	union_tok(t_msh *msh, int flag_next);
void	change_type(t_msh *msh);
///////LEXER AND UTILS//////
int		check_lexer(t_msh *msh);
int		save_smaller_than(char *smaller, t_msh *msh);
int		save_greater_than(char *greater, t_msh *msh);
int		save_pipe(t_msh *msh);
int		save_wd(char *wd, t_msh *msh);
/////////EXPAND//////////////
void	check_dollar(t_msh *msh);
//////////NODES TOK///////////////
t_tok	*new_node_tok(int type, char *content, int flag);
void	add_back_tok(t_tok **tok, t_tok *aux);
void	tok_list(t_tok **tok,int type,char *content, int flag);
//////////STRUCT CMD///////////////
void	struct_cmd(t_msh *msh);
int		calculate_matrix(t_tok *tok);
t_cmd	*return_last(t_cmd *cmd);
//////////SAVE OUTFILE/////////////
t_tok	*save_trunc(t_tok *aux, t_cmd *cmd);
t_tok	*save_append(t_tok *aux, t_cmd *cmd);
/////////SAVE INFILE//////////////
t_tok	*save_infile(t_tok *tok, t_msh *msh);
t_tok	*save_heredoc(t_tok *tok, t_msh *msh);
//////////////BUILT-INS//////////////
void    ft_echo(t_cmd *cmd);
void	ft_cd(t_msh *msh, t_cmd *cmd);
void    ft_pwd();
void    ft_env(t_msh *msh);
void	ft_sort_expt(t_msh *msh);
void	ft_add_expt(int i, t_cmd *cmd, t_env **env);
void	ft_print_expt(t_msh *msh);
int		ft_valid_identifier(t_msh *msh);
t_env	*new_node(int i);
void	ft_swap(char **a, char **b);
void	ft_export(t_msh *msh, t_cmd *cmd);
void	ft_push(t_env **env, char *name, char *content);
void    ft_pop(t_env **head, char *str);
void    ft_unset(t_msh *data, t_cmd *cmd);
void	ft_exit(t_cmd *cmd);
/////////////EXPAND_HD/////////////////
char	*check_word(char *line, int *i);
char	*joined_msh(char *line, char *aux);
char	*expand_env(char *str,t_env *env, t_msh *msh);
char	*check_env(char *str, int *i, t_msh *msh);
////////////////exeggutor/////////////////
void    ft_exeggutor(t_msh *msh, int i);
char    *ft_get_content(t_env *env, char *name);
char	*ft_get_path(t_msh *msh, t_cmd *cmd);
int     ft_builtins(t_msh *msh, t_cmd *cmd);
void    ft_child_executor(t_msh *msh, int i, int fdpipe, t_cmd *cmd);
void    ft_redirections(t_msh *msh, int i, int tmpout, t_cmd *cmd);


//////////////PRINT///////////////  
void printenv(t_env *env);

#endif