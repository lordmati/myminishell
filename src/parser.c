#include "minishell.h"

static int	syntactic_analysis(t_msh *msh, int i)
{
	t_tok	*aux;

	aux = msh->tok;
	while (aux)
	{
		if (aux->type == T_PIPE && i == 1)
			return (msj_error(ERROR_PIPES, msh, 2), 0);
		else if (aux->type >= 1 && aux->type <= 5 && aux->next == NULL)
		{
			msj_error(ERROR_NEWLINE, msh, 127);
			return (0);
		}
		else if ((aux->type >= 2 && aux->type <= 5)
			&& (aux->next->type != T_WORD
				&& aux->next->type != T_DOUBLE_QUOTE
				&& aux->next->type != T_SIMPLE_QUOTE))
		{
			msj_error(ERROR_NEWLINE, msh, 127);
			return (0);
		}
		i = 0;
		aux = aux->next;
	}
	return (1);
}

static	int	save_double_quote(char *str, t_msh *msh)
{
	int		i;
	char	*content;
	int		flag;

	i = 1;
	flag = 0;
	while (str[i] != '\"' && str[i])
		i++;
	if (str[i] == '\"')
	{
		if (str[i + 1] != '|' && str[i + 1] != '>'
			&& str[i + 1] != '<' && str[i + 1] != ' ')
			flag = 1;
		content = ft_substr(str, 1, (i++) - 1);
		tok_list(&msh->tok, T_DOUBLE_QUOTE, content, flag);
	}
	else if (str[i] == '\0')
		msj_error(ERROR_DOUBLE_QUOTES, msh, 2);
	return (i);
}

static	int	save_quote(char *str, t_msh *msh)
{
	int		i;
	char	*content;
	int		flag;

	i = 1;
	flag = 0;
	while (str[i] != '\'' && str[i])
		i++;
	if (str[i] == '\'')
	{
		if (str[i + 1] != '|' && str[i + 1] != '>'
			&& str[i + 1] != '<' && str[i + 1] != ' ')
			flag = 1;
		content = ft_substr(str, 1, (i++) - 1);
		tok_list(&msh->tok, T_SIMPLE_QUOTE, content, flag);
	}
	else if (str[i] == '\0')
		msj_error(ERROR_SIMPLE_QUOTES, msh, 2);
	return (i);
}

static void	create_tokens(t_msh *msh, int i)
{
	while (msh->prompt[i])
	{
		while (msh->prompt[i] == ' ')
			i++;
		if (msh->prompt[i] != '|' && msh->prompt[i] != '<'
			&& msh->prompt[i] != '>' && msh->prompt[i] != '\0'
			&& msh->prompt[i] != '\'' && msh->prompt[i] != '\"')
			i += save_wd(&msh->prompt[i], msh);
		else if (msh->prompt[i] == '\'')
			i += save_quote(&msh->prompt[i], msh);
		else if (msh->prompt[i] == '\"')
			i += save_double_quote(&msh->prompt[i], msh);
		else if (msh->prompt[i] == '|')
			i += save_pipe(msh);
		else if (msh->prompt[i] == '<')
			i += save_smaller_than(&msh->prompt[i], msh);
		else if (msh->prompt[i] == '>')
			i += save_greater_than(&msh->prompt[i], msh);
	}
}

int	check_lexer(t_msh *msh)
{
	int	ret;

	create_tokens(msh, 0);
	if (msh->number_error == 2 || msh->number_error == 127)
		return (0);
	ret = syntactic_analysis(msh, 1);
	return (ret);
}
