/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaguir <misaguir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:32:39 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/07/10 16:52:21 by misaguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_len(long number)
{
	int	len;

	len = 1;
	if (number < 0)
	{
		number *= -1;
		len++;
	}
	while (number > 9)
	{
		number = number / 10;
		len++;
	}
	return (len);
}

int	ft_putnbr_pf_pf(int n)
{
	int	c;

	c = ft_len(n);
	if (n == -2147483648)
		ft_putstr_pf_pf("-2147483648");
	else
	{
		if (n < 0)
		{
			n *= -1;
			ft_putchar('-');
		}
		if (n > 9)
		{
			ft_putnbr_pf_pf(n / 10);
		}
		ft_putchar((n % 10) + '0');
	}
	return (c);
}
