# include "minishell.h"

int	calculate_matrix(t_msh *msh, t_tok *tok)
{
	int i;
	t_tok *aux;
	(void)msh;

	aux = tok;
	i = 0;
	while (aux && aux->type != T_PIPE)
	{
		if (aux->type == T_WORD)
			i++;
		else if (aux->next && (aux->type >= 8 && aux->type <= 11))
			aux = aux->next;
		aux = aux->next;
	}
	return (i);
}
t_cmd *return_last(t_cmd *cmd)
{
	t_cmd *aux;

	aux = cmd;
	while (aux->next)
		aux = aux->next;
	return (aux);

}