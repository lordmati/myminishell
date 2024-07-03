#include "minishell.h"

int		ft_valid_identifier(t_msh *msh)
{
	char	**str;
	int 	i;
	int		j;

	i = 0;
	str = msh->cmd->argv;
	while(str[i])
	{
		j = 0;
		while(str[i][j])
		{
			if(ft_isdigit(str[i][0]) || !ft_isalnum(str[i][j]))
			{
				printf("export: %s: not a valid identifier\n", str[i]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_print_expt(t_msh *msh)
{
	t_env *env;
	
	env = msh->export;
	while(env)
	{
		ft_printf("declare -x %s=",env->name);
		ft_printf("%s\n",env->content);
		env = env->next;
	}
}

t_env	*new_node(int i)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->content = NULL;
	new->name = malloc(sizeof(char) * i + 1);
	new->next = NULL;
	return (new);
}