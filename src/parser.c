/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:10:46 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/14 16:11:37 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*get_commands(char **tokens);

t_command	*ms_parser(char *line)
{
	char		**tokens;
	t_command	*commands;

	tokens = ms_lexer(line);
	commands = get_commands(tokens);
	ms_clean_tokens(tokens);
	free(line);
	return (commands);
}

static t_command	*get_commands(char **tokens)
{
	t_command	*commands;

	(void) tokens;
	commands = 0;
	return (commands);
}
