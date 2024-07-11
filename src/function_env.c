/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgonzal2 <pgonzal2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:56:20 by misaguir          #+#    #+#             */
/*   Updated: 2024/07/11 12:36:46 by pgonzal2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_first_node(char **envp, t_env *node)
{
	int	i;

	i = 0;
	while (envp[0][i])
	{
		if (envp[0][i] == '=')
			break ;
		i++;
	}
	node->name = ft_calloc(sizeof(char ), i + 1);
	if (!node->name)
		return ;
	ft_strlcpy(node->name, envp[0], i);
	node->content = ft_strdup(&envp[0][++i]);
	node->next = NULL;
}

static void	take_env(t_env *aux, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[++i])
	{
		aux->next = malloc(sizeof(t_env));
		if (!aux->next)
			return ;
		aux = aux->next;
		j = -1;
		while (envp[i][++j])
		{
			if (envp[i][j] == '=')
				break ;
		}
		aux->name = ft_calloc(sizeof(char), j + 1);
		if (!aux->name)
			return ;
		ft_strlcpy(aux->name, envp[i], ++j);
		aux->content = ft_strdup(&envp[i][j]);
		aux->next = NULL;
	}
}

void	organization_env(char **envp, t_env **env)
{
	t_env	*aux;

	if (!envp[0])
		return ;
	*env = malloc(sizeof(t_env));
	if (!*env)
		return ;
	aux = *env;
	create_first_node(envp, aux);
	take_env(aux, envp);
}
