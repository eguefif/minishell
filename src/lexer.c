/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:49:23 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/13 18:37:29 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*clean_line(char *line)
{
	char	*cleaned_line;

	cleaned_line = ft_strtrim(line, " \t");
	free(line);
	clean_isolated_quotes(cleaned_line);
	return (cleaned_line);
}

char	*jump_quote(char *line)
{
	int	i;

	i = 1;
	while (line[i] != *line)
		i++;
	return (line + i);
}

size_t	count_tokens(char *line)
{
	size_t	flag;
	size_t	count;

	flag = 1;
	count = 0;
	line = clean_line(line);
	while (*line)
	{
		if (ft_strchr("\"\'", *line))
		{
			if (flag == 1)
			{
				count++;
				flag = 0;
			}
			line = jump_quote(line);
		}
		else if (!ft_strchr("\t ", *line) && flag == 1)
		{
			count++;
			flag = 0;
		}
		else if (ft_strchr("\t ", *line))
			flag = 1;
		line++;
	}
	return (count);
}

char	**ms_lexer(char *line)
{
	char	**retval;

	retval = 0;
	count_tokens(line);
	return (retval);
}
