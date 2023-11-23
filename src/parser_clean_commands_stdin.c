/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_commands_stdin.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:07:15 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/23 13:55:46 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_tokens_stdin(char *token)
{
	size_t	i;
	size_t	len;
	char	tmp;

	i = 0;
	len = ft_strlen(token);
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '\"')
		{
			tmp = token[i];
			ft_memmove(&token[i], &token[i + 1], len - i);
			while (token[i] && token[i] != tmp)
				i++;
			if (token[i] == tmp)
				ft_memmove(&token[i], &token[i + 1], len - i);
		}
		i++;
	}	
	return (token);
}
