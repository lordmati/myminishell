/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaguir <misaguir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:56:13 by misaguir          #+#    #+#             */
/*   Updated: 2024/07/10 16:56:14 by misaguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_expand(t_msh *msh, t_tok *tok)
{
	char	*aux;
	char	*line;
	int		i;

	i = 0;
	line = ft_strdup("");
	while (tok->content[i])
	{
		if (tok->content[i] == '$')
			aux = check_env(tok->content, &i, msh);
		else
			aux = check_word(tok->content, &i);
		line = joined_msh(line, aux);
	}
	free(tok->content);
	return (line);
}

void	check_dollar(t_msh *msh)
{
	t_tok	*aux;
	int		i;

	i = 0;
	aux = msh->tok;
	while (aux)
	{
		if (aux->type == T_HEREDOC)
			aux = aux->next;
		else if (aux->type == T_DOUBLE_QUOTE || aux->type == T_WORD)
		{
			i = 0;
			while (aux->content[i])
			{
				if (aux->content[i] == '$')
				{
					aux->content = check_expand(msh, aux);
					break ;
				}
				i++;
			}
		}
		aux = aux->next;
	}
}
