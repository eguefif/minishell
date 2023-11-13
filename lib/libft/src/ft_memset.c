/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:10:46 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/18 12:14:24 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	v;
	size_t			i;
	unsigned char	*retval;

	if (s == 0)
		return (0);
	v = (unsigned char) c;
	retval = (unsigned char *) s;
	i = 0;
	while (i < len)
	{
		retval[i] = v;
		i++;
	}
	return ((void *) retval);
}
