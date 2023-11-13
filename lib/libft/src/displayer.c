/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 21:03:43 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/24 08:33:44 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print(int fd, t_string string);

void	display(int fd, t_split *splits)
{
	int		i;

	i = 0;
	while (i < splits->counts)
	{
		print(fd, splits->list[i]);
		i++;
	}
}

static void	print(int fd, t_string string)
{
	if (string.string)
		write(fd, string.string, string.size);
}

void	sdisplay(char *str, t_split *splits)
{
	int		i;
	int		j;
	size_t	c;

	i = 0;
	j = 0;
	while (i < splits->counts)
	{
		c = 0;
		while (c < splits->list[i].size)
		{
			str[j] = splits->list[i].string[c];
			c++;
			j++;
		}
		i++;
	}
}
