#include "minishell.h"

void	ft_sort_expt(t_msh *msh)
{
	t_env	*one;
	t_env	*other;

	one = msh->export;
	while (one && one->next)
	{
		other = msh->export;
		while (other->next)
		{
			if (ft_strncmp(other->name, other->next->name,
					ft_strlen(other->name)) > 0)
			{
				ft_swap(&other->name, &other->next->name);
				ft_swap(&other->content, &other->next->content);
			}
			other = other->next;
		}
		one = one->next;
	}
}

static void	ft_addback(t_env **export, t_env *aux)
{
	t_env	*actual;

	if (!*export)
		*export = aux;
	else
	{
		actual = *export;
		while (actual->next != NULL)
			actual = actual->next;
		actual->next = aux;
	}
}

void	ft_push(t_env **env, char *name, char *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	node->name = name;
	node->content = content;
	node->next = NULL;
	ft_pop(env, node->name);
	ft_addback(env, node);
}

void	ft_add_expt(int i, t_cmd *cmd ,t_env **env)
{
	char	**str;
	t_env	*aux;
	int		j;

	aux = *env;
	str = cmd->argv;
	while (str[++i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '=')
				break ;
			j++;
		}
		aux = new_node(j);
		ft_strlcpy(aux->name, str[i], ++j);
		if (str[i][j - 1] != '=')
			aux->content = ft_strdup("");
		else
			aux->content = ft_strdup(&str[i][j]);
		ft_pop(env, aux->name);
		ft_addback(env, aux);
		aux->next = NULL;
	}
}

void	ft_export(t_msh *msh, t_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd->len_argv > 1)
	{
		if (!ft_valid_identifier(msh))
			return ;
		ft_add_expt(0, cmd, &msh->export);
		while (cmd->argv[++i])
		{
			if (ft_strchr(cmd->argv[i], '='))
				ft_add_expt(0, cmd, &msh->env);
		}
	}
	else
	{
		ft_sort_expt(msh);
		ft_print_expt(msh);
	}
}
