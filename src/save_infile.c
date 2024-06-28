#include "minishell.h"

static void	call_get_next_line(t_tok *tok, t_msh *msh)
{
	char	*line;
	int		fd;

	line = ft_strdup("");
	fd = open(".heredoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		printf("Error al crear fd\n");
	while (line)
	{
		free(line);
		line = get_next_line(0);
		if (ft_strncmp(line, tok->content, ft_strlen(line) - 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
	}
	close(fd);
	unlink(".heredoc.tmp");
	msh->cmd->fdin = open("heredoc.tmp", O_RDONLY);
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
	tok = tok->next;
	call_get_next_line(tok, msh);
	tok = tok->next;
	return (tok);
}
