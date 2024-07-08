#include "minishell.h"

static void	ft_child_executor2(t_msh *msh, int i, int fdpipe, t_cmd *cmd)
{
	char	*path;

	msh->pids[i] = fork();
	if (msh->pids[i] == 0)
	{
		path = ft_get_path(msh, cmd);
		if (!path)
			return ((void)perror("path"));
		execve(path, cmd->argv, msh->envp);
		perror("exec");
		exit(errno);
	}
	else    //da un error mas 
	{
		if (i < msh->len_cmds - 1)
			close(fdpipe);
	}
}
void	ft_exeggutor(t_msh *msh, int i)
{
	int	tmpin;
	int	tmpout;
	int	fdpipe[2];
	t_cmd	*cmd;
	//char 	*path;

	cmd = msh->cmd;
	if (!cmd)
		return ;
	msh->pids = malloc(sizeof(int) * msh->len_cmds);
	tmpin = dup(0);
	tmpout = dup(1);
	if (cmd->fdin == -1)
		cmd->fdin = dup(tmpin);
	if (msh->len_cmds == 1)
	{
		if (!ft_builtins(msh, cmd))
		{
			ft_redirections(msh, ++i, tmpout, cmd);
			// path = ft_get_path(msh, cmd);
			// if (!path)
			// 	return ((void)perror("path"));
			// execve(path, cmd->argv, msh->envp);
			// perror("exec");
			ft_child_executor2(msh, i, fdpipe[1], cmd);
		}
	}
	else
	{
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
	waitpid(msh->pids[msh->len_cmds - 1], &msh->number_status, 0);
	msh->number_status = WEXITSTATUS(msh->number_status);
	ft_kill_children(msh->pids, msh->len_cmds - 1);
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
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
		if (!ft_builtins(msh,cmd))
		{
			path = ft_get_path(msh, cmd);
			if (!path)
				return ((void)perror("path"));
			execve(path, cmd->argv, msh->envp);
			perror("exec");
			exit(errno);
		}
		else
			exit (msh->status);
	}
	else    //da un error mas 
	{
		if (i < msh->len_cmds - 1)
			close(fdpipe);
	}
}


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
	content_splited = ft_split(content, ':');
	while (content_splited[++j] != NULL)
	{
		path = ft_strjoin(content_splited[j], "/");
		path = ft_strjoin(path, cmd->argv[0]);
		if (access(path, X_OK) == 0)
			return (path);
	}
	return (NULL);
}
