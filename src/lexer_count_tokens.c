/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_count_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:00:07 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/17 14:01:45 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*jump_quote(char *line);
static void		change_state(size_t *count, int *flag, int flag_value);
static char		*handle_quotes(char *line, size_t *count, int *flag);

size_t	count_tokens(char *line)
{
	int		flag;
	size_t	count;

	flag = 1;
	count = 0;
	while (*line)
	{
		if (ft_strchr("\"\'", *line))
			line = handle_quotes(line, &count, &flag);
		else if (!ft_strchr("\t <>|", *line) && flag == 1)
			change_state(&count, &flag, 0);
		if (ft_strchr("<>|", *line))
		{
			if (*(line + 1) && *(line + 1) == *line && *(line + 1) != '|')
				line++;
			change_state(&count, &flag, 1);
		}
		else if (ft_strchr("\t ", *line))
			flag = 1;
		line++;
	}
	return (count);
}

static char	*handle_quotes(char *line, size_t *count, int *flag)
{
	if (*flag == 1)
		change_state(count, flag, 0);
	line = jump_quote(line);
	return (line);
}

static void	change_state(size_t *count, int *flag, int flag_value)
{
	*flag = flag_value;
	*count += 1;
}

static char	*jump_quote(char *line)
{
	int	i;

	i = 1;
	while (line[i] != *line)
		i++;
	return (line + i);
}
