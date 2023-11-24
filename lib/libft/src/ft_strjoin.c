/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 08:41:08 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/24 14:39:03 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*retval;

	retval = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (retval == 0)
		return (NULL);
	ft_strlcpy(retval, (char *) s1, ft_strlen((char *)s1) + 1);
	return (ft_strncat(retval, (char *)s2, ft_strlen((char *) s2)));
}
