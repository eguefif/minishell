/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 06:52:39 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/18 12:18:11 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned int		i;

	i = 0;
	if (n <= 0)
		return (0);
	while ((unsigned char)s1[i] != '\0'
		&& (unsigned char)s2[i] != '\0' && i < n - 1)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			break ;
		i++;
	}
	return ((int)(unsigned char)s1[i] - (unsigned char) s2[i]);
}
