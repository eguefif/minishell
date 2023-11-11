/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 09:31:37 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/08 13:47:03 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rec(int nb)
{
	int		figure;

	if (nb == 0)
		return ;
	else
		rec(nb / 10);
	figure = nb % 10;
	if (figure < 0)
		figure *= -1;
	ft_putchar(figure + '0');
}

void	ft_putnbr(int n)
{
	if (n == 0)
		ft_putchar('0');
	else if (n < 0)
	{
		ft_putchar('-');
		rec(n);
	}
	else
		rec(n);
}
