/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:10:46 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/16 18:09:16 by eguefif          ###   ########.fr       */
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
	parser_clean_commands(commands);
	ms_free_tokens(tokens);
	return (commands);
}
