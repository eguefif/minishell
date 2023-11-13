/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:15:40 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/17 17:11:21 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

char	*ft_strncpy(char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s2[i] && i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = s2[i];
	if (i < n)
	{
		s1[i] = '\0';
		i++;
	}
	return (s1);
}
