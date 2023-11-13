/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:11:41 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/21 17:13:26 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	is_retline(char *buffer);
static int	clear_buffer(char *line, int size);
static void	reset(char *line, char *buffer);

char	*get_next_line(int fd)
{
	static int	retval = 0;
	static char	buffer[BUFFER_SIZE];
	char		*line;

	line = 0;
	if (fd < 0 || fd > 256)
		return (NULL);
	if (*buffer)
		build_line(&line, buffer, retval);
	while (is_retline(line) == -1)
	{
		retval = read(fd, buffer, BUFFER_SIZE);
		if (retval < 0)
		{
			reset(line, buffer);
			return (NULL);
		}
		if (retval <= 0)
			break ;
		if (!build_line(&line, buffer, retval))
			return (NULL);
	}
	retval = clear_buffer(buffer, retval);
	return (line);
}

static int	clear_buffer(char *buffer, int size)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (buffer[i] != '\n' && i < size)
		i++;
	if (buffer[i] == '\n')
		i++;
	while (i < size)
	{
		buffer[j] = buffer[i];
		i++;
		j++;
	}
	return (j);
}

static int	is_retline(char *buffer)
{
	int		i;

	i = 0;
	if (!buffer)
		return (-1);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static void	reset(char *line, char *buffer)
{
	if (line)
		free(line);
	buffer[0] = '\0';
}
