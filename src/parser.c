/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:10:46 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/15 17:07:49 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ms_parser(char *line)
{
	char		**tokens;
	t_command	*commands;

	tokens = ms_lexer(line);
	if (!tokens)
		return (0);
	commands = get_commands(tokens);
	ms_clean_tokens(tokens);
	return (commands);
}
