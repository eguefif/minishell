/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 07:42:29 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/23 16:32:23 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	if (*s1 != *s2 && *s1 == '\0')
		return (1);
	return (0);
}

char	*ft_strstr(const char *str, const char *to_find)
{
	char	*retval;

	retval = 0;
	if (!str)
		return (0);
	if (!to_find)
		return (0);
	if (*to_find == '\0')
		retval = (char *) str;
	while (*str != '\0' && *to_find != '\0')
	{
		if (*str == *to_find)
		{
			if (cmp(str, to_find) == 0)
			{
				retval = (char *) str;
				break ;
			}
		}
		str++;
	}
	return (retval);
}
