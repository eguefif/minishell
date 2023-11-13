/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:49:20 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/13 16:19:44 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*retval;
	size_t	size;

	if (!s)
		return (0);
	if (start <= (unsigned int) ft_strlen((char *)s))
	{
		size = ft_strlen(&s[start]);
		if (len > size)
			len = size;
		retval = (char *) malloc(sizeof(char) * (len + 1));
		if (retval == 0)
			return (0);
		ft_strlcpy(retval, (s + start), len + 1);
	}
	else
	{
		retval = (char *) malloc(sizeof(char));
		if (retval == 0)
			return (0);
		retval[0] = '\0';
	}
	return (retval);
}
