/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_splits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:46:13 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/21 17:25:05 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*goto_convend(const char *str);
static const char	*goto_nextconv(const char *str);

t_split	*init_splits(const char *str)
{
	t_split	*splits;

	splits = 0;
	splits = (t_split *) malloc(sizeof(t_split));
	if (!splits)
		return (0);
	splits->list = 0;
	splits->counts = 0;
	splits->counts = get_counts(str);
	if (splits->counts <= 0)
		return (splits);
	splits->list = (t_string *) malloc(sizeof(t_string) * splits->counts);
	if (!splits->list)
	{
		splits->counts = 0;
		return (splits);
	}
	return (splits);
}

int	get_counts(const char *str)
{
	int		counts;

	counts = 0;
	if (ft_strlen(str) == 0)
		return (0);
	if (!*str)
		return (0);
	while (*str)
	{
		counts++;
		if (*str == '%')
			str = goto_convend(str);
		else
			str = goto_nextconv(str);
		if (!*str)
			break ;
		str++;
	}
	return (counts);
}

static const char	*goto_convend(const char *str)
{
	str++;
	if (*str == '%')
		return (str);
	while (!is_convspe_end(*str) && *str)
		str++;
	return (str);
}

static const char	*goto_nextconv(const char *str)
{
	while (*str != '%' && *str)
		str++;
	if (*str == '%')
		str--;
	return (str);
}

char	*is_convspe_end(char c)
{
	return (ft_strchr(CONVSPE, c));
}
