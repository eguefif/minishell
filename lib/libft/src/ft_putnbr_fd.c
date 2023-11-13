/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 09:31:37 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/08 10:01:57 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rec(int nb, int fd)
{
	int		figure;

	if (nb == 0)
		return ;
	else
		rec(nb / 10, fd);
	figure = nb % 10;
	if (figure < 0)
		figure *= -1;
	ft_putchar_fd(figure + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		ft_putchar_fd('0', fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		rec(n, fd);
	}
	else
		rec(n, fd);
}
