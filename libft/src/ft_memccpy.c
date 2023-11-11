/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:29:37 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/17 17:08:18 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	if (n == 0)
		return (0);
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	while (i < n && s[i] != (unsigned char) c)
	{
		d[i] = s[i];
		i++;
	}
	if (i < n)
		return ((void *) &d[i + 1]);
	else
		return (0);
}
