/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:05:39 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/14 15:24:49 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strldup(char *s1, size_t size)
{
	char	*ret;

	if (!s1)
		return ((void *) 0);
	ret = malloc(sizeof(char) * (size + 1));
	if (!(ret))
		return ((void *) 0);
	ft_strlcpy(ret, s1, size + 1);
	return (ret);
}
