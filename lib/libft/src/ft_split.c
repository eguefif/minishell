/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 08:50:39 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/25 14:07:18 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_splits_counts(char const *s, char c);
static void		free_mem(char **retval, size_t n);
static size_t	get_size(char const *s, char c);
static char		**make_tab(char **retval,
					size_t counts, char const *s, char c);

char	**ft_split(char const *s, char c)
{
	size_t	counts;
	char	**retval;

	while (*s == c && *s)
		s++;
	counts = get_splits_counts(s, c);
	retval = (char **) malloc(sizeof(char *) * (counts + 1));
	if (retval == 0)
		return (0);
	retval = make_tab(retval, counts, s, c);
	return (retval);
}

static char	**make_tab(char **retval, size_t counts, char const *s, char c)
{
	size_t	i;
	size_t	size;
	char	*string;

	i = -1;
	while (++i < counts)
	{
		size = get_size(s, c);
		string = (char *) malloc((size + 1) * sizeof(char));
		if (string == 0)
		{
			free_mem(retval, i);
			return (0);
		}
		ft_strlcpy(string, s, size + 1);
		string[size] = '\0';
		retval[i] = string;
		s += size;
		while (*s == c && *s != '\0')
			s++;
	}
	retval[i] = 0;
	return (retval);
}

static size_t	get_splits_counts(char const *s, char c)
{
	size_t	count;

	if (!c && *s)
		return (1);
	if (!*s || !s)
		return (0);
	count = 1;
	while (*s)
	{
		if (*s == c)
		{
			count++;
			while (*s == c && *s)
				s++;
		}
		else
			s++;
	}
	if (*(s - 1) == c)
		count--;
	return (count);
}

static size_t	get_size(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	free_mem(char **retval, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(retval[i]);
		i++;
	}
	free(retval);
}
