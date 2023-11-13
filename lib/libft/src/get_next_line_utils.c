/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:30:03 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/21 11:57:33 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strncat(char *dest, char *src, unsigned int nb);
static char	*ft_strncpy(char *s1, const char *s2, size_t n);
static int	ft_strlen(char *str);

/*
int	buffer_size(char *buffer)
{
	int		i;

	i = 0;
	while (i < BUFFER_SIZE && buffer[i])
		i++;
	return (i);
}
*/

int	build_line(char **line, char *buffer, int size)
{
	char	*tmp;

	if (size == 0)
		return (0);
	if (!(*line))
	{
		*line = (char *) malloc (sizeof(char) * (size + 1));
		if (!*line)
			return (0);
		ft_strncpy(*line, buffer, size);
		(*line)[size] = '\0';
		return (1);
	}
	tmp = (char *) malloc(ft_strlen(*line) + (size + 1) * sizeof(char));
	if (!tmp)
	{
		free(line);
		return (0);
	}
	ft_strncpy(tmp, *line, ft_strlen(*line));
	free(*line);
	ft_strncat(tmp, buffer, size);
	*line = tmp;
	return (1);
}

static char	*ft_strncpy(char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s2[i])
	{
		s1[i] = s2[i];
		if (s1[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

static char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	char			*retval;
	unsigned int	i;

	retval = dest;
	i = 0;
	while (*dest != '\0')
		dest++;
	while (i < nb)
	{
		*dest = *src;
		if (*dest == '\n')
		{
			dest++;
			break ;
		}
		dest++;
		src++;
		i++;
	}
	*dest = '\0';
	return (retval);
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
