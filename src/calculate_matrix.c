/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaguir <misaguir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:56:04 by misaguir          #+#    #+#             */
/*   Updated: 2024/07/10 16:56:05 by misaguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calculate_matrix(t_tok *tok)
{
	int		i;
	t_tok	*aux;

	aux = tok;
	i = 0;
	while (aux && aux->type != T_PIPE)
	{
		if (aux->type == T_WORD)
			i++;
		else if (aux->next && (aux->type >= 2 && aux->type <= 5))
			aux = aux->next;
		aux = aux->next;
	}
	return (i);
}

t_cmd	*return_last(t_cmd *cmd)
{
	t_cmd	*aux;

	aux = cmd;
	while (aux->next)
		aux = aux->next;
	return (aux);
}
