/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:36:47 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/14 14:10:34 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*retval;
	size_t	i;

	retval = (char *) malloc((size + 1) * sizeof(char));
	if (retval == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		retval[i] = '\0';
		i++;
	}
	retval[i] = '\0';
	return (retval);
}
