#include "minishell.h"

void	ft_unset(t_msh *msh)
{
	char	*str;
	int		i;

	i = 0;
	while (msh->cmd->argv[i])
	{
		str = msh->cmd->argv[i];
		ft_pop(&msh->env, str);
		ft_pop(&msh->export, str);
		i++;
	}
	return ;
}

static void	ft_free_node(t_env *node)
{
	free(node->name);
	free(node->content);
	free(node);
}

void	ft_pop(t_env **head, char *str)
{
	t_env	*previous;
	t_env	*current;

	if (*head == NULL)
		return ;
	current = *head;
	if (ft_strncmp(current->name, str, ft_strlen(str)+1) == 0)
	{
		*head = (*head)->next;
		ft_free_node(current);
		return ;
	}
	previous = *head;
	current = (*head)->next;
	while (current && ft_strncmp(current->name, str, ft_strlen(str)+1))
	{
		previous = current;
		current = current->next;
	}
	if (current)
	{
		previous->next = current->next;
		ft_free_node(current);
	}
}
