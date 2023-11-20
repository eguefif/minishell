/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:10:46 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/20 17:42:08 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_tokens(char **tokens);

t_command	*ms_parser(char *line, char **env)
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
	parser_clean_commands(commands, env);
	ms_free_tokens(tokens);
	return (commands);
}

int	check_tokens(char **tokens)
{
	int		i;

	i = -1;
	if (tokens[0] && tokens[0][0] == '|')
	{
		ft_error_message(tokens[0], SYNTAX_ERROR);
		return (0);
	}
	while (tokens[++i])
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
	}
	return (1);
}
