/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 08:28:48 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/04 08:41:50 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_nbr(const char *s, int sign)
{
	long unsigned int	nbr;
	int					retval;
	extern int			errno;

	nbr = 0;
	while (*s >= '0' && *s <= '9')
	{
		nbr *= 10;
		nbr += *s - '0';
		s++;
	}
	if (nbr > 2147483647 && sign >= 0)
	{
		errno = ERANGE;
		retval = 2147483647;
	}
	else if (nbr > 2147483648 && sign < 0)
	{
		errno = ERANGE;
		retval = -2147483648;
	}
	else
		retval = sign * nbr;
	return (retval);
}

int	ft_atoi(const char *s)
{
	int		sign;

	while ((*s == '\n' || *s == '\t' || *s == '\v' || *s == '\r'
			|| *s == '\f' || *s == ' ') && *s)
		s++;
	if (!*s)
		return (0);
	if (s[0] == '-')
	{
		sign = -1;
		s++;
	}
	else if (s[0] == '+')
	{
		s++;
		sign = 1;
	}
	else
		sign = 1;
	return (get_nbr(s, sign));
}
