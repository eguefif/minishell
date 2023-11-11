/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:33:49 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/21 17:24:43 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clean(t_split *splits)
{
	int		i;

	if (splits)
	{
		if (splits->list)
		{
			i = 0;
			while (i < splits->counts)
			{
				if (splits->list[i].string)
					free(splits->list[i].string);
				i++;
			}
			free(splits->list);
		}
		free(splits);
	}
}
