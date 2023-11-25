/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_strnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:42:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/24 16:56:49 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_strnum(char *str)
{
	if (*str == '-')
		str++;
	while (*str)
	{
		ft_printf("%c\n", str);
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
