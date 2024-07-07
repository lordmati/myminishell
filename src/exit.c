#include "minishell.h"

static int	ft_special_atoi(char *str)
{
	int		signo;
	long	num;
	int		i;

	i = 0;
	num = 0;
	signo = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			signo *= -1;
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		num = (num * 10) + (str[i] - '0');
		++i;
	}
	if (num > 255)
		return ((int)(num-1) % 255);
	return ((int)(num) % 255);
}

void	ft_exit(t_cmd *cmd)
{
	int	num;

	num = 0;
	if (cmd->len_argv > 2)
	{
		ft_putstr_fd("Error: too many arguments\n", 1);
		ft_putstr_fd("exit\n", 1);
		return ;
	}
	else if (cmd->len_argv == 2)
	{
		num = ft_special_atoi(cmd->argv[1]);
		if (num == 255)
		{
			ft_putstr_fd("Error: numeric argument required\n", 1);
			exit(num);
		}
	}
	ft_putstr_fd("exit\n", 1);
	exit (num);
}
