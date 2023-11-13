/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lutoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:28:33 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/18 15:07:32 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_nbr_size(unsigned long int nbr, char *base);
static void	lutoa(unsigned long int nbr, char *base, int size, char *retval);

char	*ft_lutoa_base(unsigned long int nbr, char *base)
{
	char	*retval;
	int		size;

	if (nbr == 0)
	{
		retval = ft_strnew(1);
		retval[0] = base[0];
	}
	else
	{
		size = get_nbr_size(nbr, base);
		retval = ft_strnew(size);
		lutoa(nbr, base, size - 1, retval);
	}
	return (retval);
}

static int	get_nbr_size(unsigned long int nbr, char *base)
{
	int		size;

	size = 0;
	while (nbr != 0)
	{
		nbr /= ft_strlen(base);
		size++;
	}
	return (size);
}

static void	lutoa(unsigned long int nbr, char *base, int size, char *retval)
{
	if (nbr == 0)
		return ;
	else
		lutoa(nbr / ft_strlen(base), base, size - 1, retval);
	retval[size] = base[nbr % ft_strlen(base)];
}
