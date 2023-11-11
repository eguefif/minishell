/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:46:04 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/18 14:59:08 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		size;
	int		i;
	char	*retval;

	if (!s)
		return (0);
	size = ft_strlen((char *) s);
	i = 0;
	retval = ft_strnew(size);
	if (retval == 0)
		return (0);
	while (s[i])
	{
		retval[i] = f(i, s[i]);
		i++;
	}
	retval[i] = '\0';
	return (retval);
}
