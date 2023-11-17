/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_token_size.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:16:32 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/17 14:17:57 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_chevron_size(char *line);
static size_t	get_other_size(char *line);

size_t	get_token_size(char *line)
{
	size_t	retval;

	retval = 0;
	if (ft_strchr("<>", *line))
		retval = get_chevron_size(line);
	else if (*line == '|')
		retval = 1;
	else
		retval = get_other_size(line);
	return (retval);
}

static size_t	get_chevron_size(char *line)
{
	if ((line + 1) && (*(line + 1) == *line))
		return (2);
	return (1);
}

static size_t	get_other_size(char *line)
{
	size_t	retval;
	size_t	i;

	retval = 0;
	while (line[retval] && !ft_strchr(TOKENS, line[retval]))
	{
		if (ft_strchr("\'\"", line[retval]))
		{
			i = 1;
			while (line[retval + i] && line[retval + i] != line[retval])
				i++;
			retval += i;
		}
		retval++;
	}
	return (retval);
}
