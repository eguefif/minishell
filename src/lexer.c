/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:49:23 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/16 13:11:23 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		clean_isolated_quotes(char *line);
static char		*jump_quote(char *line);

char	**ms_lexer(char *line)
{
	char	**retval;
	size_t	size;
	char	*cleaned_line;

	retval = 0;
	cleaned_line = clean_line(line);
	size = count_tokens(cleaned_line);
	retval = get_tokens(cleaned_line, size);
	ms_clean_tokens(retval);
	free(cleaned_line);
	return (retval);
}

char	*clean_line(char *line)
{
	char	*cleaned_line;

	cleaned_line = ft_strtrim(line, " \t\n");
	clean_isolated_quotes(cleaned_line);
	return (cleaned_line);
}

static void	clean_isolated_quotes(char *line)
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
		else if (ft_strchr("<>|", *line))
		{
			if (*(line + 1) && *(line + 1) == *line && *(line + 1) != '|')
				line++;
			count++;
			flag = 1;
		}
		else if (ft_strchr("\t ", *line))
			flag = 1;
		line++;
	}
	return (count);
}

static char	*jump_quote(char *line)
{
	int	i;

	i = 1;
	while (line[i] != *line)
		i++;
	return (line + i);
}
