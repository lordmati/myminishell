/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaguir <misaguir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:56:46 by misaguir          #+#    #+#             */
/*   Updated: 2024/07/10 17:22:22 by misaguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

void	heredoc_handler(int signum)
{
	(void)signum;
	exit(130);
}

void	signal_d(t_msh *msh)
{
	free_msh(msh);
	ft_free_env(&msh->env);
	ft_free_env(&msh->export);
	printf("exit\n");
	exit(msh->status);
}

void	signal_c(int signal)
{
	(void)signal;
	if (g_sig == 1)
	{
		write(1, "\033[K\n", 5);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_sig == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		write(1, "\033[K\n", 5);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	signal_quit(int signal)
{
	(void)signal;
	write(2, "Quit (core dumped)\n", 20);
}

void	init_signal(void)
{
	signal(SIGTSTP, SIG_IGN);
	if (g_sig == 0)
		signal(SIGQUIT, SIG_IGN);
	else
		signal(SIGQUIT, signal_quit);
	signal(SIGINT, signal_c);
}
