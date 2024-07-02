#include "minishell.h"

static char	*check_expand_hd(t_msh *msh, char *str)
{
	char	*aux;
	char	*line;
	int 	i;

	i = 0;
	line = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
			aux = check_env(str, &i, msh);
		else
			aux = check_word(str, &i);
		line = joined_msh(line, aux);
	}
	free(str);
	return (line);
}

static void	expand_hd(char *line, t_msh *msh)
{
	char	*aux;
	int		i;

	i = 0;
	aux = ft_strdup(line);
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{
			aux = check_expand_hd(msh, aux);
			break ;
		}
		i++;
	}
	free(line);
	line = ft_strdup(aux);
	free(aux);
}

static void	call_get_next_line(t_tok *tok, t_msh *msh)
{
	char	*line;
	int		fd;

	line = readline("Heredoc > ");
	fd = open(".heredoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		printf("Error al crear fd\n");
	while (line)
	{
		if (ft_strncmp(line, tok->content, ft_strlen(tok->content) + 1) == 0)
		{
			free(line);
			break ;
		}
		expand_hd(line, msh);
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("Heredoc > ");
	}
	close(fd);
	msh->cmd->fdin = open(".heredoc.tmp", O_RDONLY);
	unlink(".heredoc.tmp");
}


t_tok	*save_infile(t_tok *tok, t_msh *msh)
{
	t_cmd *last;

	last = return_last(msh->cmd);
	tok = tok->next;
	if (last->fdin >= 3)
		close (last->fdin);
	msh->cmd->fdin = open(tok->content, O_RDONLY);
	if (msh->cmd->fdin == -1)
	{
		msh->cmd->error = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tok->content, 2);
		msj_error(ERROR_NO_FILE, msh, 1);
	}
	tok = tok->next;
	return (tok);
}

t_tok	*save_heredoc(t_tok *tok, t_msh *msh)
{
	t_cmd *last;

	last = return_last(msh->cmd);
	tok = tok->next;
	if (last->fdin >= 3)
		close (last->fdin);
	call_get_next_line(tok, msh);
	tok = tok->next;
	return (tok);
}
