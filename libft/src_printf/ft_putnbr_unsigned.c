/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaguir <misaguir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:45:50 by pgonzal2          #+#    #+#             */
/*   Updated: 2024/07/10 16:52:29 by misaguir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_len(long number)
{
	int	len;

	len = 1;
	while (number > 9)
	{
		number = number / 10;
		len++;
	}
	return (len);
}

int	ft_putnbr_pf_unsigned(unsigned int n)
{
	int	c;

	c = ft_len(n);
	if (n > 9)
	{
		ft_putnbr_pf_unsigned(n / 10);
	}
	ft_putchar((n % 10) + '0');
	return (c);
}
