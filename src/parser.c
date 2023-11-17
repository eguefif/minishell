/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:10:46 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/17 13:11:19 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_tokens(char **tokens);

t_command	*ms_parser(char *line)
{
	char		**tokens;
	t_command	*commands;

	if (!line)
		return (0);
	tokens = ms_lexer(line);
	if (!check_tokens(tokens))
	{
		ms_free_tokens(tokens);
		return (0);
	}
	if (!tokens)
		return (0);
	commands = get_commands(tokens);
	parser_clean_commands(commands);
	ms_free_tokens(tokens);
	return (commands);
}

int	check_tokens(char **tokens)
{
	int		i;

	i = 0;
	if (tokens[i] && tokens[i][0] == '|')
	{
		ft_error_message(tokens[i], SYNTAX_ERROR);
		return (0);
	}
	while (tokens[i])
	{
		if (ft_strchr("<>|", tokens[i][0]))
		{
			if (!tokens[i + 1])
			{
				ft_error_message(tokens[i], SYNTAX_ERROR);
				return (0);
			}
			if (ft_strchr("<>|", tokens[i + 1][0]))
			{
				ft_error_message(tokens[i + 1], SYNTAX_ERROR);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
