/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:50:42 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/16 14:16:12 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_token_size(char *line);
size_t	get_chevron_size(char *line);
size_t	get_other_size(char *line);

char **get_tokens(char *line, size_t size)
{
	char	**retval;
	size_t	token_size;
	size_t	i;

	retval = 0;
	retval = (char **) malloc(sizeof(char *) * (size + 1));
	if (retval == 0)
	{
		ft_error();
		return (0);
	}
	retval[size] = 0;
	i = 0;
	while (i < size)
	{
		while (ft_strchr(" \t", *line))
			line++;
		token_size = get_token_size(line);
		retval[i] = ft_strldup(line, token_size);
		if (retval[i] == 0)
		{
			ms_free_tokens(retval);
			ft_error();
			return (0);
		}
		line += token_size;
		i++;
	}
	return (retval);
}

size_t	get_token_size(char *line)
{
	size_t retval;

	retval = 0;
	if (ft_strchr("<>", *line))
		retval = get_chevron_size(line);
	else if (*line == '|')
		retval = 1;
	else
		retval = get_other_size(line);
	return (retval);
}

size_t	get_chevron_size(char *line)
{
	if ((line + 1) && (*(line + 1) == *line))
			return (2);
	return (1);
}

size_t	get_other_size(char *line)
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
