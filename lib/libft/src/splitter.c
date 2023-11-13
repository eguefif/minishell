/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:26:08 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/21 17:24:53 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			get_splits(t_split *splits, const char *str);
static int			split_size(const char *str);
static void			copy(char *s, const char *s2, unsigned int size);
static int			is_init_error(t_split *splits);

t_split	*split(const char *str)
{
	t_split	*splits;

	splits = 0;
	splits = init_splits(str);
	if (is_init_error(splits))
		return (splits);
	if (!get_splits(splits, str))
	{
		clean(splits);
		return (0);
	}
	return (splits);
}

static int	is_init_error(t_split *splits)
{
	return (!splits || splits->counts == 0 || !splits->list);
}

static int	get_splits(t_split *splits, const char *str)
{
	int		i;
	int		size;

	i = 0;
	while (i < splits->counts)
	{
		size = split_size(str);
		splits->list[i].string = ft_strnew(size);
		if (!splits->list[i].string)
		{
			splits->counts = i;
			return (0);
		}
		copy(splits->list[i].string, str, size);
		splits->list[i].string[size] = '\0';
		splits->list[i].size = size;
		str += size;
		i++;
	}
	return (1);
}

static int	split_size(const char *str)
{
	int		size;

	if (str[0] == '%')
	{
		size = 1;
		while (!is_convspe_end(str[size]) && str[size])
			size++;
		if (str[size])
			size++;
	}
	else
	{
		size = 0;
		while (str[size] != '%' && str[size])
			size++;
	}
	return (size);
}

static void	copy(char *s, const char *s2, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		s[i] = s2[i];
		i++;
	}
}
