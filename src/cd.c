/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaguir <misaguir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:56:02 by misaguir          #+#    #+#             */
/*   Updated: 2024/07/10 16:56:03 by misaguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_msh *msh, t_cmd *cmd)
{
	char	*content;
	char	buffer[1000];

	if (cmd->len_argv == 1 || !ft_strncmp(cmd->argv[1], "~\0", 2))
	{
		content = ft_get_content(msh->env, "HOME");
		if (!content)
			perror("error");
	}
	else if (!ft_strncmp(cmd->argv[1], "-\0", 2))
	{
		content = ft_get_content(msh->env, "OLDPWD");
		if (!content)
			perror("error");
	}
	else
		content = cmd->argv[1];
	getcwd(buffer, 1000);
	if (chdir(content) < 0)
		perror("chdir");
	ft_push(&msh->export, ft_strdup("OLDPWD"), ft_strdup(buffer));
	ft_push(&msh->env, ft_strdup("OLDPWD"), ft_strdup(buffer));
	getcwd(buffer, 1000);
	ft_push(&msh->export, ft_strdup("PWD"), ft_strdup(buffer));
	ft_push(&msh->env, ft_strdup("PWD"), ft_strdup(buffer));
}
