/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaguir <misaguir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:56:49 by misaguir          #+#    #+#             */
/*   Updated: 2024/07/10 16:56:50 by misaguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tok	*save_redirection(t_tok *tok, t_msh *msh)
{
	while (tok && tok->type != T_PIPE)
	{
		if (tok->type == T_REDIRECTION_OUTFILE)
			tok = save_trunc(tok, msh->cmd, msh);
		else if (tok->type == T_APPEND)
			tok = save_append(tok, msh->cmd, msh);
		else if (tok->type == T_REDIRECTION_INFILE)
			tok = save_infile(tok, msh);
		else if (tok->type == T_HEREDOC)
			tok = save_heredoc(tok, msh);
		else if (tok->type == T_WORD)
			tok = tok->next;
	}
	return (tok);
}

static void	add_back_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*node;

	if (!*cmd)
		return ;
	else
	{
		node = *cmd;
		while ((*cmd)->next != NULL)
			*cmd = (*cmd)->next;
		(*cmd)->next = new;
		*cmd = node;
	}
}

static t_cmd	*new_node_cmd(int i, t_tok *tok)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = ft_calloc(sizeof(char *), i + 1);
	if (!cmd->argv)
		return (NULL);
	cmd->len_argv = i;
	i = 0;
	while (tok && tok->type != T_PIPE)
	{
		if (tok->type == T_WORD)
			cmd->argv[i++] = ft_strdup(tok->content);
		else if (tok->next && (tok->type >= 2 && tok->type <= 5))
			tok = tok->next;
		tok = tok->next;
	}
	cmd->error = 0;
	cmd->fdin = -1;
	cmd->fdout = -1;
	cmd->argv[i] = NULL;
	cmd->next = NULL;
	return (cmd);
}

static t_tok	*create_node_cmd(t_tok *tok, t_msh *msh)
{
	t_tok	*aux;
	t_cmd	*new;
	int		i;

	aux = tok;
	msh->len_cmds += 1;
	i = calculate_matrix(msh->tok);
	if (msh->cmd)
	{
		new = new_node_cmd(i, tok);
		add_back_cmd(&msh->cmd, new);
	}
	else
		msh->cmd = new_node_cmd(i, tok);
	aux = save_redirection(aux, msh);
	return (aux);
}

void	struct_cmd(t_msh *msh)
{
	t_tok	*aux;

	aux = msh->tok;
	while (aux != NULL)
	{
		if (aux->type != T_PIPE)
			aux = create_node_cmd(aux, msh);
		else
			aux = aux->next;
	}
}
