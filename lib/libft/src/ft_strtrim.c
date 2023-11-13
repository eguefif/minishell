/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:53:52 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/13 15:15:04 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*retval;

	if (!*s1 || !s1)
		retval = ft_strnew(0);
	else if (!*set)
		retval = ft_strdup(s1);
	else
	{
		while (is_charset(set, *s1) && *s1)
			s1++;
		i = 0;
		while (s1[i])
			i++;
		i--;
		while (is_charset(set, s1[i]) && i >= 0)
			i--;
		retval = ft_substr(s1, 0, i + 1);
	}
	return (retval);
}
