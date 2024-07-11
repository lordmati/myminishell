/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaguir <misaguir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:56:40 by misaguir          #+#    #+#             */
/*   Updated: 2024/07/10 16:56:41 by misaguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*save_append(t_tok *aux, t_cmd *cmd, t_msh *msh)
{
	t_cmd	*last;

	last = return_last(cmd);
	aux = aux->next;
	if (last->fdout >= 3)
		close (last->fdout);
	if (last->error == 0)
		last->fdout = open(aux->content, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (last->fdout == -1)
	{
		last->error = 1;
		msj_error("Conchita: Permission denied", msh, 1);
	}
	aux = aux->next;
	return (aux);
}

t_tok	*save_trunc(t_tok *aux, t_cmd *cmd, t_msh *msh)
{
	t_cmd	*last;

	last = return_last(cmd);
	aux = aux->next;
	if (last->fdout >= 3)
		close (last->fdout);
	if (last->error == 0)
		last->fdout = open(aux->content, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (last->fdout == -1)
	{
		last->error = 1;
		msj_error("Conchita: Permission denied", msh, 1);
	}
	aux = aux->next;
	return (aux);
}
