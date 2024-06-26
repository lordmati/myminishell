#include "minishell.h"

static void	init_struck(t_msh *msh)
{
	msh->cmd = NULL;
	msh->tok = NULL;
	msh->len_cmds = 0;
	msh->number_status = 0;
	msh->number_error = 0;
}

void	msj_error(char *str, t_msh *msh, int status)
{
	msh->number_status = status;
	msh->number_error = status;
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
			check_dollar(&msh);
			union_tok(&msh, 1);
			change_type(&msh);
			struct_cmd(&msh);
			msh.envp = envp;
			ft_exeggutor(&msh, -1);
			free_msh(&msh);
		}
		msh.prompt = readline("prueba mi conchita$ ");
	}
	return (0);
}
