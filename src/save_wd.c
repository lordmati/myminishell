/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_wd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaguir <misaguir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:56:37 by misaguir          #+#    #+#             */
/*   Updated: 2024/07/10 16:56:44 by misaguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_wd(char *wd, t_msh *msh)
{
	int		i;
	char	*content;

	i = 0;
	while (wd[i] != '|' && wd[i] != '<' && wd[i] != '>'
		&& wd[i] != ' ' && wd[i] != '\0' && wd[i] != '\''
		&& wd[i] != '\"')
		i++;
	content = ft_substr(wd, 0, i);
	if (wd[i] == '\'' || wd[i] == '\"')
		tok_list(&msh->tok, T_WORD, content, 1);
	else
		tok_list(&msh->tok, T_WORD, content, 0);
	return (i);
}
