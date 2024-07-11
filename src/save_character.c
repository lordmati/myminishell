/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_character.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaguir <misaguir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:56:31 by misaguir          #+#    #+#             */
/*   Updated: 2024/07/10 16:56:32 by misaguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_smaller_than(char *smaller, t_msh *msh)
{
	char	*content;

	if (smaller[0] == '<' && smaller[1] == '<')
	{
		content = ft_strdup("<<");
		tok_list(&msh->tok, T_HEREDOC, content, 0);
		return (2);
	}
	else
	{
		content = ft_strdup("<");
		tok_list(&msh->tok, T_REDIRECTION_INFILE, content, 0);
		return (1);
	}
}

int	save_greater_than(char *greater, t_msh *msh)
{
	char	*content;

	if (greater[0] == '>' && greater[1] == '>')
	{
		content = ft_strdup(">>");
		tok_list(&msh->tok, T_APPEND, content, 0);
		return (2);
	}
	else
	{
		content = ft_strdup(">");
		tok_list(&msh->tok, T_REDIRECTION_OUTFILE, content, 0);
		return (1);
	}
}

int	save_pipe(t_msh *msh)
{
	char	*content;

	content = ft_strdup("|");
	tok_list(&msh->tok, T_PIPE, content, 0);
	return (1);
}
