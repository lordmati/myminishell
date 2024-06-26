/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaguir <misaguir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:53:17 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/06/28 18:48:33 by misaguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_echo(t_cmd *cmd)
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
	while(cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], 1);
		if(i < cmd->len_argv - 1)
			write(1, " ", 1);
		i++;
	}
	if(!n_flag)
		write(1, "\n", 1);
}

void	ft_pwd()
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if(!cwd)
		perror("error");
	printf("%s\n", cwd);
	free(cwd);
}

void	ft_env(t_msh *msh)
{
	t_env *env;
	
	env = msh->env;
	while(env)
	{
		ft_printf("%s=",env->name);
		ft_printf("%s\n",env->content);
		env = env->next;
	}
}
