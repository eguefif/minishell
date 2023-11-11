/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_precision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 08:55:36 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/27 12:02:25 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*make_precision(char *nbr, t_conv conv)
{
	int		i;
	char	*tmp;
	int		start;

	if (conv.precision < ft_strlen(nbr))
		return (nbr);
	tmp = (char *) malloc((conv.precision + 1) * sizeof(char));
	i = 0;
	while (i < conv.precision)
	{
		tmp[i] = '0';
		i++;
	}
	start = conv.precision - ft_strlen(nbr);
	i = 0;
	while (start < conv.precision && nbr[i])
	{
		tmp[start] = nbr[i];
		start++;
		i++;
	}
	tmp[start] = '\0';
	free(nbr);
	return (tmp);
}
