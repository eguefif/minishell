/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 07:42:29 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/18 14:32:02 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cmp(const char *s1, const char *s2, size_t i, size_t len)
{
	while (*s1 != '\0' && *s2 != '\0' && i < len)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
		i++;
	}
	if ((*s1 != *s2) && (*s1 == '\0'))
		return (1);
	if (*s2 != '\0' && i == len)
		return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*retval;
	size_t		i;

	retval = 0;
	i = 0;
	if (*needle == '\0' || !needle)
		retval = haystack;
	while (*haystack && *needle && i < len)
	{
		if (*haystack == *needle)
		{
			if (cmp(haystack, needle, i, len) == 0)
			{
				retval = haystack;
				break ;
			}
		}
		haystack++;
		i++;
	}
	return ((char *) retval);
}
