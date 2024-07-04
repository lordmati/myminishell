#include "minishell.h"

void	ft_exeggutor(t_msh *msh, int i)
{
	int	tmpin;
	int	tmpout;
	int	fdpipe[2];

	if (!msh->cmd)
		return ;
	msh->pids = malloc(sizeof(int) * msh->len_cmds);
	tmpin = dup(0);
	tmpout = dup(1);
	if (msh->cmd->fdin == -1)
		msh->cmd->fdin = dup(tmpin);
	while (++i < msh->len_cmds)
	{
		ft_redirections(msh, i, tmpout);
		ft_child_executor(msh, i, fdpipe[1]);
		msh->cmd = msh->cmd->next;
	}
	waitpid(msh->pids[msh->len_cmds - 1], NULL, 0);
	ft_kill_children(msh->pids, msh->len_cmds - 1);
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
}

void	ft_redirections(t_msh *msh, int i, int tmpout)
{
	int	fdpipe[2];

	dup2(msh->cmd->fdin, 0);
	close(msh->cmd->fdin);
	if (i == msh->len_cmds - 1)
	{
		if (msh->cmd->fdout == -1)
			msh->cmd->fdout = dup(tmpout);
	}
	else
	{
		pipe(fdpipe);
		msh->cmd->next->fdin = fdpipe[0];
		if (msh->cmd->fdout == -1)
			msh->cmd->fdout = fdpipe[1];
		else
			close(fdpipe[1]);
	}
	dup2(msh->cmd->fdout, 1);
	close(msh->cmd->fdout);
}

void	ft_child_executor(t_msh *msh, int i, int fdpipe)
{
	char	*path;

	if (!ft_builtins(msh))
	{
		msh->pids[i] = fork();
		if (msh->pids[i] == 0)
		{
			path = ft_get_path(msh);
			if (!path)
				return ((void)perror("path"));
			execve(path, msh->cmd->argv, msh->envp);
			perror("exec");
			exit(1);
		}
		else
		{
			if (i < msh->len_cmds - 1)
				close(fdpipe);
		}
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

char	*ft_get_path(t_msh *msh)
{
	char	**content_splited;
	int		j;
	char	*path;
	char	*content;

	j = -1;
	if (access(msh->cmd->argv[0], X_OK) == 0)
		return (msh->cmd->argv[0]);
	content = ft_get_content(msh->env, "PATH");
	if (!content)
		return (NULL);
	content_splited = ft_split(content, ':');
	while (content_splited[++j] != NULL)
	{
		path = ft_strjoin(content_splited[j], "/");
		path = ft_strjoin(path, msh->cmd->argv[0]);
		if (access(path, X_OK) == 0)
			return (path);
	}
	return (NULL);
}
