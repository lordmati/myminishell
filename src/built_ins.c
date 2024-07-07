#include "minishell.h"

int	ft_builtins(t_msh *msh)
{
	//msh->len_cmds--;
	if (msh->cmd->argv[0] == NULL)
		return (1);
	if (!ft_strncmp(msh->cmd->argv[0], "echo\0", 5))
		return (ft_echo(msh->cmd), 1);
	else if (!ft_strncmp(msh->cmd->argv[0], "cd\0", 3))
		return (ft_cd(msh), 1);
	else if (!ft_strncmp(msh->cmd->argv[0], "export\0", 7))
		return (ft_export(msh), 1);
	else if (!ft_strncmp(msh->cmd->argv[0], "unset\0", 6))
		return (ft_unset(msh), 1);
	else if (!ft_strncmp(msh->cmd->argv[0], "pwd\0", 4))
		return (ft_pwd(), 1);
	else if (!ft_strncmp(msh->cmd->argv[0], "env\0", 4))
		return (ft_env(msh), 1);
	else if (!ft_strncmp(msh->cmd->argv[0], "exit\0", 5))
		return (ft_exit(msh->cmd), 1);
	return (0);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (cmd->argv[i] && (!ft_strncmp(cmd->argv[i], "-n", 3)))
	{
		n_flag = 1;
		i++;
	}
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		if (i < cmd->len_argv - 1)
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
}

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("error");
	dprintf(2, "%s\n", cwd);
	free(cwd);
}

void	ft_env(t_msh *msh)
{
	t_env	*env;

	env = msh->env;
	while (env)
	{
		ft_printf("%s=", env->name);
		ft_printf("%s\n", env->content);
		env = env->next;
	}
}
