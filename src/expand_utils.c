#include "minishell.h"

char	*check_word(char *line, int *i)
{
	int		j;
	int		len;
	char	*ret;

	len = 0;
	j = *i;
	while (line[j] && line[j] != '$')
	{
		j++;
		len++;
	}
	ret = malloc(sizeof (char *) * (len + 1));
	if (!ret)
		return (NULL);
	j = 0;
	while (line[*i] && line[*i] != '$')
		ret[j++] = line[(*i)++];
	ret[j] = '\0';
	return (ret);
}

char	*joined_msh(char *line, char *aux)
{
	int		i;
	int		size;
	char	*ret;
	int		j;

	j = 0;
	i = 0;
	size = ft_strlen(line) + ft_strlen(aux);
	ret = (char *)malloc(sizeof(char) * size + 1);
	if (ret == NULL)
		return (NULL);
	while (line[i] != '\0')
	{
		ret[i] = line[i];
		i++;
	}
	while (aux[j] != '\0')
		ret[i++] = aux[j++];
	free(line);
	free(aux);
	ret[i] = '\0';
	return (ret);
}

char	*expand_env(char *str, t_env *env, t_msh *msh)
{
	int		len;
	t_env	*aux;

	aux = env;
	len = ft_strlen(str);
	while (aux)
	{
		if (ft_strncmp(str, "?", 1) == 0)
			return (ft_itoa(msh->number_status));
		else if (ft_strncmp(str, aux->name, len) == 0 && aux->name[len] == '\0')
			return (ft_strdup(aux->content));
		aux = aux->next;
	}
	return (ft_strdup(""));
}

char	*check_env(char *str, int *i, t_msh *msh)
{
	char	*aux;
	char	*ret;
	int		start;

	start = *i + 1;
	*i += 1;
	while (str[*i] != '\0')
	{
		if ((!ft_isalnum(str[*i]) || str[*i] == '_') && str[*i] != '?')
			break ;
		else if (str[*i] == '?')
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
	aux = ft_substr(str, start, (*i - start));
	ret = expand_env(aux, msh->env, msh);
	free(aux);
	return (ret);
}
