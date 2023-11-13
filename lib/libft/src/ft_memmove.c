/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:25:36 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/11 19:00:56 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_overlapping(unsigned char *to, unsigned char *from, size_t n)
{
	return (to > from && (size_t)(to - from) < n);
}

void	copy_from_the_end(unsigned char *to, unsigned char *from, size_t n)
{
	int	i;

	i = n - 1;
	while (i >= 0)
	{
		to[i] = from[i];
		if (i == 0)
			return ;
		i--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*to;
	unsigned char	*from;

	to = (unsigned char *) dest;
	from = (unsigned char *) src;
	if (!from || !to || dest == src || n == 0)
		return (dest);
	if (is_overlapping(to, from, n))
	{
		copy_from_the_end(to, from, n);
		return (dest);
	}
	ft_memcpy(to, from, n);
	return (dest);
}
