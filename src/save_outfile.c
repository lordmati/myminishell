#include "minishell.h"

t_tok	*save_append(t_tok *aux, t_cmd *cmd)
{
	t_cmd *last;

	last = return_last(cmd);
	aux = aux->next;
	if (last->fdout >= 3)
		close (last->fdout);
	if (last->error == 0)
		last->fdout = open(aux->content, O_RDWR | O_CREAT | O_APPEND, 0644);
	aux = aux->next;
	return (aux);
}

t_tok	*save_trunc(t_tok *aux, t_cmd *cmd)
{
	t_cmd *last;

	last = return_last(cmd);
	aux = aux->next;
	if (last->fdout >= 3)
		close (last->fdout);
	if (last->error == 0)
		last->fdout = open(aux->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
	aux = aux->next;
	return (aux);
}
