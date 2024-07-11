/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeggutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:55:59 by misaguir          #+#    #+#             */
/*   Updated: 2024/07/11 13:04:07 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exeggutor(t_msh *msh, int i)
{
	int		tmpin;
	int		tmpout;
	t_cmd	*cmd;

	cmd = msh->cmd;
	if (!cmd)
		return ;
	msh->pids = ft_calloc(sizeof(int), msh->len_cmds);
	tmpin = dup(0);
	tmpout = dup(1);
	if (cmd->fdin == -1)
		cmd->fdin = dup(tmpin);
	if (msh->len_cmds == 1)
		one_cmd(msh, cmd, i, tmpout);
	else
		multiple_cmds(msh, cmd, i, tmpout);
	cleanup_process_execution(msh, tmpin, tmpout);
}

void	ft_redirections(t_msh *msh, int i, int tmpout, t_cmd *cmd)
{
	int	fdpipe[2];

	dup2(cmd->fdin, 0);
	close(cmd->fdin);
	if (i == (msh->len_cmds - 1))
	{
		if (cmd->fdout == -1)
			cmd->fdout = dup(tmpout);
	}
	else
	{
		pipe(fdpipe);
		cmd->next->fdin = fdpipe[0];
		if (cmd->fdout == -1)
			cmd->fdout = fdpipe[1];
		else
			close(fdpipe[1]);
	}
	dup2(cmd->fdout, 1);
	close(cmd->fdout);
}

void	ft_child_executor(t_msh *msh, int i, int fdpipe, t_cmd *cmd)
{
	char	*path;

	msh->pids[i] = fork();
	if (msh->pids[i] == 0)
	{
		if (!ft_builtins(msh, cmd))
		{
			path = ft_get_path(msh, cmd);
			if (!path)
			{
				perror("path");
				exit(errno);
			}
			execve(path, cmd->argv, msh->envp);
			perror("exec");
			exit(errno);
		}
		else
			exit (msh->status);
	}
	else
	{
		if (i < msh->len_cmds - 1)
			close(fdpipe);
	}
}

void	ft_only_son(t_msh *msh, int i, int fdpipe, t_cmd *cmd)
{
	char	*path;

	msh->pids[i] = fork();
	if (msh->pids[i] == 0)
	{
		path = ft_get_path(msh, cmd);
		if (!path)
		{
			perror("path");
			exit(errno);
		}
		execve(path, cmd->argv, msh->envp);
		perror("exec");
		exit(errno);
	}
	else
	{
		if (i < msh->len_cmds - 1)
			close(fdpipe);
	}
}

char	*ft_get_path(t_msh *msh, t_cmd *cmd)
{
	char	**content_splited;
	int		j;
	char	*path;
	char	*content;

	j = -1;
	if (access(cmd->argv[0], X_OK) == 0)
		return (cmd->argv[0]);
	content = ft_get_content(msh->env, "PATH");
	if (!content)
		return (NULL);
	content_splited = find_executable_in_path(cmd, msh, content);
	while (content_splited[++j] != NULL)
	{
		path = ft_strjoin(content_splited[j], "/");
		path = ft_strjoin_gnl(path, cmd->argv[0]);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	if (content_splited[j] == NULL)
		msj_error("command not found", msh, 127);
	exit (msh->number_status);
}
