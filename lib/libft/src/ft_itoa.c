/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 09:43:23 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/18 12:24:22 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
{
	int		i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	rec(char *nbr, int n, int position)
{
	int		figure;

	if (n == 0)
		return ;
	else
		rec(nbr, n / 10, position - 1);
	figure = n % 10;
	if (figure < 0)
		figure *= -1;
	nbr[position] = figure + '0';
}

static char	*get_zero(void)
{
	char	*nbr;

	nbr = (char *) malloc(sizeof(char) * (1 + 1));
	if (nbr == 0)
		return (0);
	nbr[0] = '0';
	nbr[1] = '\0';
	return (nbr);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*nbr;

	size = get_size(n);
	if (n == 0)
		nbr = get_zero();
	else if (n < 0)
	{
		nbr = (char *) malloc(sizeof(char) * (size + 2));
		if (nbr == 0)
			return (0);
		nbr[0] = '-';
		nbr[size + 1] = '\0';
		rec(nbr, n, size);
	}
	else
	{
		nbr = (char *) malloc(sizeof(char) * (size + 1));
		if (nbr == 0)
			return (0);
		rec(nbr, n, size - 1);
		nbr[size] = '\0';
	}
	return (nbr);
}
