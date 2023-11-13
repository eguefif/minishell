/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:35:41 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/24 08:29:51 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_overall_size(t_split *splits);

/*	Design
 * 1. We split the string into regular string and conversion specifier(conv).
 * 2. We replace each conversion specifier string by an ad hoc string.
 * 3. We display the  each splits.
 * 4. We calculate the overall size and return the value
 */

int	ft_printf(const char *str, ...)
{
	int		size;
	t_split	*splits;
	va_list	ap;

	size = 0;
	splits = split(str);
	if (splits && splits->counts > 0)
	{
		va_start(ap, str);
		if (replace_conversion(splits, ap))
		{
			display(1, splits);
			va_end(ap);
			size = get_overall_size(splits);
		}
		else
			size = -1;
	}
	if (!splits)
		size = -1;
	clean(splits);
	return (size);
}

static int	get_overall_size(t_split *splits)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (i < splits->counts)
	{
		if (splits->list[i].string)
			size += splits->list[i].size;
		i++;
	}
	return (size);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	int		size;
	t_split	*splits;
	va_list	ap;

	size = 0;
	splits = split(str);
	if (splits && splits->counts > 0)
	{
		va_start(ap, str);
		if (replace_conversion(splits, ap))
		{
			display(fd, splits);
			va_end(ap);
			size = get_overall_size(splits);
		}
		else
			size = -1;
	}
	if (!splits)
		size = -1;
	clean(splits);
	return (size);
}

int	ft_sprintf(char *buffer, const char *str, ...)
{
	int		size;
	t_split	*splits;
	va_list	ap;

	size = 0;
	splits = split(str);
	if (splits && splits->counts > 0)
	{
		va_start(ap, str);
		if (replace_conversion(splits, ap))
		{
			sdisplay(buffer, splits);
			va_end(ap);
			size = get_overall_size(splits);
		}
		else
			size = -1;
	}
	if (!splits)
		size = -1;
	clean(splits);
	return (size);
}
