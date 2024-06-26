#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# define ERROR_PIPES "bash: syntax error near unexpected token `|'"
# define ERROR_NEWLINE "bash: syntax error near unexpected token `newline'"
# define ERROR_DOUBLE_QUOTES "bash: expected to close the double quote"
# define ERROR_SIMPLE_QUOTES "bash: expected to close the quote"
# define ERROR_NO_FILE ": No such file or directory"
# define ERROR_SLASH "bash: expected to scape character"

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
	T_PIPE = 7,
	T_HEREDOC = 8,
	T_APPEND = 9,
	T_REDIRECTION_INFILE = 10,
	T_REDIRECTION_OUTFILE = 11,
	T_WORD = 12,
	T_SIMPLE_QUOTE = 13,
	T_DOUBLE_QUOTE = 14,
}	t_tok_type;

typedef enum e_stats
{
	S_INIT = 1,
	S_WORD = 2,
	S_QUOTE = 3,
	S_DOUBLE_QUOTE = 4,
	S_DOLLAR = 5,
	S_DOLLAR_DOUBLE_QUOTE = 6
}	t_stats;

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
	char	**envp;
}	t_msh;
////////BORRAR*///////
void	print_token(t_tok *tok);
///////ENVP////////
void	organization_env(char **envp, t_env **env);
////////FREE///////
void	free_msh(t_msh *msh);
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
int		calculate_matrix(t_msh *msh, t_tok *tok);
t_cmd	*return_last(t_cmd *cmd);
//////////SAVE OUTFILE/////////////
t_tok	*save_trunc(t_tok *aux, t_cmd *cmd);
t_tok	*save_append(t_tok *aux, t_cmd *cmd);
/////////SAVE INFILE//////////////
t_tok	*save_infile(t_tok *tok, t_msh *msh);
t_tok	*save_heredoc(t_tok *tok, t_msh *msh);
//////////////BUILT-INS//////////////
void    ft_echo(t_cmd *cmd);
void	ft_cd(t_msh *msh);
void    ft_pwd();
void    ft_env(t_msh *msh);
void	ft_sort_expt(t_msh *msh);
void	ft_add_expt(t_msh *msh, int i, int j, t_env **env);
void	ft_swap(char **a, char **b);
void	ft_export(t_msh *msh);
void    ft_pop(t_env **head, char *str);
void    ft_unset(t_msh *data);
void	ft_exit(t_cmd *cmd);

////////////////exeggutor/////////////////
void    ft_exeggutor(t_msh *msh, int i);
char    *ft_get_content(t_env *env, char *name);
char	*ft_get_path(t_msh *msh);
int     ft_builtins(t_msh *msh);
int    	ft_child_process(t_msh *msh, int ret, int i, int fdpipe);
int    ft_redirection(t_msh *msh, int i, int tmpout);


//////////////PRINT///////////////  
void printenv(t_env *env);

#endif