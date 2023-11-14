/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:49:23 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/14 15:48:50 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_isolated_quotes(char *line);
char	*clean_line(char *line);
size_t	count_tokens(char *line);

char	**ms_lexer(char *line)
{
	char	**retval;
	size_t	size;

	retval = 0;
	line = clean_line(line);
	size = count_tokens(line);
	get_tokens(line, size);
	return (retval);
}

char	*clean_line(char *line)
{
	char	*cleaned_line;

	cleaned_line = ft_strtrim(line, " \t");
	free(line);
	clean_isolated_quotes(cleaned_line);
	return (cleaned_line);
}

void	clean_isolated_quotes(char *line)
{
	int	i;

	while (*line)
	{
		if (*line == 34 || *line == 39)
		{
			i = 1;
			while (line[i] && line[i] != *line)
				i++;
			if (!line[i])
				ft_memmove(line, line + 1, i);
			else
				line += (i + 1);
		}
		else
			line++;
	}
}

size_t	count_tokens(char *line)
{
	size_t	flag;
	size_t	count;

	flag = 1;
	count = 0;
	while (*line)
	{
		if (!ft_strchr("\t ", *line) && flag == 1)
		{
			if (ft_strchr("\"\'", *line))
				line = jump_quote(line);
			count++;
			flag = 0;
		}
		else if (ft_strchr("\t ", *line))
			flag = 1;
		line++;
	}
	return (count);
}

char	*jump_quote(char *line)
{
	int	i;

	i = 1;
	while (line[i] != *line)
		i++;
	return (line + i);
}
