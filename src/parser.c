/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:10:46 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/17 11:56:06 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ms_parser(char *line)
{
	char		**tokens;
	t_command	*commands;

	if (!line)
		return (0);
	tokens = ms_lexer(line);
	if (!tokens)
		return (0);
	commands = get_commands(tokens);
	parser_clean_commands(commands);
	ms_free_tokens(tokens);
	return (commands);
}
