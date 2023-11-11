/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:52:11 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/18 09:11:19 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		v;
	const unsigned char	*str;
	size_t				i;

	if (!s)
		return (0);
	str = (const unsigned char *) s;
	v = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (str[i] == v)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
