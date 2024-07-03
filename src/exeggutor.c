#include "minishell.h"

void ft_exeggutor(t_msh *msh, int i)
{
    int tmpin;
    int tmpout;
    int ret;
    int fdpipe;

    tmpin = dup(0);
    tmpout = dup(1);
    if (!msh->cmd)
        return ;
    if (msh->cmd->fdin == -1)
        msh->cmd->fdin = dup(tmpin); 
    while (++i < msh->len_cmds)
    {
        ft_printf("i: %i, fd:  %d\n", i, msh->cmd->fdout);
        if (msh->cmd->error == 0)
        {
            fdpipe = ft_redirection(msh, i, tmpout);
            ret = ft_child_process(msh, ret);
        }
        msh->cmd = msh->cmd->next;
    }
    dup2(tmpin, 0);
    dup2(tmpout, 1);
    close(tmpin);
    close(tmpout);
}

int    ft_child_process(t_msh *msh, int ret)
{
    char    *path;

    if (!ft_builtins(msh))
    {
        ret = fork();
        if (ret == 0)
        {
            path = ft_get_path(msh);
            if (!path)
                return (perror("path"), 0);
            execve(path, msh->cmd->argv, msh->envp);
            perror("exec");
            exit(1);
        }
        // else  // Parent process
        //    {
        //        waitpid(ret, NULL, 0);
        //        // Close the write end of the pipe in the parent
        //        if (i < msh->len_cmds - 1)
        //            close(fdpipe);
        //    }
    }
    return (ret);
}

int    ft_redirection(t_msh *msh, int i, int tmpout)
{
    int fdpipe[2];

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
        msh->cmd->fdout = fdpipe[1];
        msh->cmd->next->fdin = fdpipe[0];
    }
    dup2(msh->cmd->fdout, 1);
    close(msh->cmd->fdout);
    return (fdpipe[1]);
}

int    ft_builtins(t_msh *msh)
{
    if (msh->cmd->argv[0] == NULL)
        return (1);
    if (!ft_strncmp(msh->cmd->argv[0], "echo", 4))
        return (ft_echo(msh->cmd), 1);
    else if (!ft_strncmp(msh->cmd->argv[0], "cd", 2))
        return (ft_cd(msh), 1);
    else if (!ft_strncmp(msh->cmd->argv[0], "export\0", 7))
        return (ft_export(msh), 1);
    else if (!ft_strncmp(msh->cmd->argv[0], "unset", 5))
        return (ft_unset(msh), 1);
    else if (!ft_strncmp(msh->cmd->argv[0], "pwd", 3))
        return (ft_pwd(), 1);
    else if (!ft_strncmp(msh->cmd->argv[0], "env", 3))
        return (ft_env(msh), 1);
    else if (!ft_strncmp(msh->cmd->argv[0], "exit", 4))
        ft_exit(msh->cmd);
    return (0);
}

char    *ft_get_content(t_env *env, char *name)
{
    while (env != NULL && env->next != NULL)
    {
        if (ft_strncmp(env->name, name, ft_strlen(name)+1) == 0)
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
		if(access(path, X_OK) == 0)
			return (path);
	}
	return (NULL);
}
