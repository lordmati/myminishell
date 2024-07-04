#include "minishell.h"

void	heredoc_handler(int signum)
{
	(void)signum;
	exit(130);
}


void	signal_d(t_msh *msh)
{
	free_msh(msh);
	printf("exit\n");
	exit(msh->status);
}

void	signal_c(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void init_signal(void)
{
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_c);
}
