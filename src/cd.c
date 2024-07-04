#include "minishell.h"

void	ft_cd(t_msh *msh)
{
	char	*content;
	char	buffer[1000];

	if (msh->cmd->len_argv == 1)
	{
		content = ft_get_content(msh->env, "HOME");
		if (!content)
			perror("error");
	}
	else if (!ft_strncmp(msh->cmd->argv[1], "-", 1))
	{
		content = ft_get_content(msh->env, "OLDPWD");
		if (!content)
			perror("error");
	}
	else
		content = msh->cmd->argv[1];
	getcwd(buffer, 1000);
	if (chdir(content) < 0)
		perror("chdir");
	ft_push(&msh->export, ft_strdup("OLDPWD"), ft_strdup(buffer));
	ft_push(&msh->env, ft_strdup("OLDPWD"), ft_strdup(buffer));
	getcwd(buffer, 1000);
	ft_push(&msh->export, ft_strdup("PWD"), ft_strdup(buffer));
	ft_push(&msh->env, ft_strdup("PWD"), ft_strdup(buffer));
}
