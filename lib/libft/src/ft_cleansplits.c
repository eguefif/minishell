/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleansplits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:06:35 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/16 18:01:45 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_cleansplits(char **splits)
{
	int		i;

	i = 0;
	if (splits)
	{
		while (splits[i])
			free(splits[i++]);
		free(splits);
	}
}
