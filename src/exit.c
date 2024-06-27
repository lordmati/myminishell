#include "minishell.h"

static int ft_special_atoi(char *str)
{
    int     signo;
    long    num;
    int     i;

    i = 0;
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
    if (!num || num < INT_MIN || num > INT_MAX)
        return (255);
    return ((int)num * signo);
}

void	ft_exit(t_cmd *cmd)
{
	int num;

	if (cmd->len_argv > 2)
		ft_putstr_fd("error: too many arguments\n", 1);
	else if (cmd->len_argv == 2)
	{
		num = ft_special_atoi(cmd->argv[1]);
		if (num == 255)
		{
			ft_putstr_fd("error: numeric argument required\n", 1);
			exit(num);
		}
	}
	ft_putstr_fd("exit\n", 1);
	exit (0);
}
