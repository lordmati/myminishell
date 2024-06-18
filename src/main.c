#include "minishell.h"

static void	init_struck(t_msh *msh)
{
	msh->cmd = NULL;
	msh->tok = NULL;
	msh->fdin = -1;
	msh->fdout = -1;
	msh->len_cmds = 0;
}

void	msj_error(char *str)
{
	ft_putendl_fd(str, 2);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;

	(void)argc;
	(void)argv;
	init_struck(&msh);
	organization_env(envp, &msh.env);
	organization_env(envp, &msh.export);
	msh.prompt = readline("prueba mi conchita$ ");
	while (msh.prompt)
	{
		if (!ft_strlen(msh.prompt))
		{
			msh.prompt = readline("prueba mi conchita$ ");
			continue ;
		}
		add_history(msh.prompt);
		if (check_lexer(&msh) == 1)
		{
			union_tok(&msh, 1);
			change_type(&msh);
			struct_cmd(&msh);
		}
		msh.envp = envp;
		ft_exeggutor(&msh);
		msh.prompt = readline("prueba mi conchita$ ");
		free_msh(&msh);
	}
	return (0);
}