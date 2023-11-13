/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 08:19:18 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/13 18:03:05 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*retval;
	int		size;

	if (!s)
		return (0);
	size = ft_strlen((char *)s);
	if (size > 0)
	{
		retval = (char *) malloc(sizeof(char) * (size + 1));
		if (retval == 0)
			return (0);
		ft_strlcpy(retval, s, size + 1);
	}
	else
	{
		retval = (char *) malloc(sizeof(char) * 1);
		if (retval == 0)
			return (0);
		retval[0] = '\0';
	}
	return (retval);
}
