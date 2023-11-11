/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 08:08:08 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/23 11:25:40 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	strlcat_l(char *dest, char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (*dest != '\0' && i < size)
	{
		dest++;
		i++;
	}
	while (*src != '\0' && size - 1 > i)
	{
		*dest = *src;
		dest++;
		src++;
		i++;
	}
	*dest = '\0';
}

size_t	ft_strlcat(char *dest, char *src, size_t dstsize)
{
	unsigned int	dest_size;
	unsigned int	src_size;

	if (!dest || !src)
		return (0);
	dest_size = ft_strlen(dest);
	src_size = ft_strlen(src);
	if (dstsize <= dest_size)
		return (dstsize + ft_strlen(src));
	strlcat_l(dest, src, dstsize);
	return (dest_size + src_size);
}
