/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 06:52:39 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/17 11:52:06 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
	{
		if (s1)
			return ((unsigned char) *s1);
		if (s2)
			return (0 - (unsigned char) *s2);
		return (0);
	}
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	return ((unsigned char) *s1 - (unsigned char) *s2);
}
