/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeggutor_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:17:34 by misaguir          #+#    #+#             */
/*   Updated: 2024/07/11 12:33:00 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_content(t_env *env, char *name)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name) + 1) == 0)
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

char	**find_executable_in_path(t_cmd *cmd, t_msh *msh, char *content)
{
	char	**content_splited;

	content_splited = ft_split(content, ':');
	if (ft_strlen(cmd->argv[0]) == 0)
	{
		msj_error("command not found", msh, 127);
		exit(msh->number_status);
	}
	return (content_splited);
}

void	cleanup_process_execution(t_msh *msh, int tmpin, int tmpout)
{
	waitpid(msh->pids[msh->len_cmds - 1], &msh->number_status, 0);
	msh->number_status = WEXITSTATUS(msh->number_status);
	ft_kill_children(msh->pids, msh->len_cmds - 1);
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
}

void	one_cmd(t_msh *msh, t_cmd *cmd, int i, int tmpout)
{
	int	fdpipe[2];

	if (!cmd->error)
	{
		if (!ft_builtins(msh, cmd))
		{
			ft_redirections(msh, ++i, tmpout, cmd);
			ft_only_son(msh, i, fdpipe[1], cmd);
		}
	}
}

void	multiple_cmds(t_msh *msh, t_cmd *cmd, int i, int tmpout)
{
	int	fdpipe[2];

	while (++i < msh->len_cmds)
	{
		if (!cmd->error)
		{
			ft_redirections(msh, i, tmpout, cmd);
			ft_child_executor(msh, i, fdpipe[1], cmd);
		}
		else
			msh->len_cmds--;
		cmd = cmd->next;
	}
}
