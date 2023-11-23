/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_commands_stdin.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:07:15 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/23 13:22:49 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_quotes_number(char *token);

char	*clean_tokens_stdin(char *token)
{
	size_t	size;
	size_t	i;
	size_t	j;	
	char	*retval;

	size = get_quotes_number(token);
	retval = (char *) malloc(sizeof(char) * (size + 1));
	if (!retval)
	{
		free(token);
		return (0);
	}
	retval[size] = 0;
	i = 0;
	j = 0;
	while (i < size)
	{
		if (!ft_strchr("\'\"", token[i]))	
		{
			retval[j] = token[i];
			j++;
		}
		i++;
	}	
	return (retval);
}

size_t	get_quotes_number(char *token)
{
	size_t	retval;
	int		i;

	retval = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '\"')
			retval++;
		i++;
	}
	return (retval);
}
