/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:50:42 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/17 14:18:15 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		handle_error(char **retval);
static char		*ignore_space_and_tab(char *line);
size_t			get_token_size(char *line);

char	**get_tokens(char *line, size_t size)
{
	char	**retval;
	size_t	token_size;
	size_t	i;

	retval = (char **) malloc(sizeof(char *) * (size + 1));
	if (retval == 0)
	{
		ft_error();
		return (0);
	}
	retval[size] = 0;
	i = -1;
	while (++i < size)
	{
		line = ignore_space_and_tab(line);
		token_size = get_token_size(line);
		retval[i] = ft_strldup(line, token_size);
		if (retval[i] == 0)
		{
			handle_error(retval);
			return (0);
		}
		line += token_size;
	}
	return (retval);
}

static char	*ignore_space_and_tab(char *line)
{
	while (ft_strchr(" \t", *line))
		line++;
	return (line);
}

static void	handle_error(char **retval)
{
	ms_free_tokens(retval);
	ft_error();
}
