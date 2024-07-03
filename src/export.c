#include "minishell.h"

void	ft_swap(char **a, char **b)
{
	char *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort_expt(t_msh *msh)
{
	t_env	*one;
	t_env	*other;
	
	one = msh->export;
	while (one && one->next)
	{
		other = msh->export;
		while(other->next)
		{
			if(ft_strncmp(other->name, other->next->name, ft_strlen(other->name)) > 0)
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
	t_env *node;

	node = malloc(sizeof(t_env));
	node->name = name;
	node->content = content;
	node->next = NULL;
	ft_pop(env, node->name);
	ft_addback(env, node);
}

void	ft_add_expt(t_msh *msh, int i, int j, t_env **env)
{
	char 	**str;
	t_env	*aux;

	aux = *env;
	str = msh->cmd->argv;
	while(str[++i])
	{
		j = 0;
		while(str[i][j])
		{
			if (str[i][j] == '=')
				break;
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

void	ft_export(t_msh *msh)
{
	int i;

	i = -1;
	if(msh->cmd->len_argv > 1)
	{
		if (!ft_valid_identifier(msh))
			return ;
		ft_add_expt(msh, 0, 0, &msh->export);
		while(msh->cmd->argv[++i])
		{
			if (ft_strchr(msh->cmd->argv[i], '='))
				ft_add_expt(msh, 0, 0, &msh->env);
		}
	}
	else
	{
		ft_sort_expt(msh);
    	ft_print_expt(msh);
	}
}