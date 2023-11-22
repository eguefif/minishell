/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:17:01 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/17 14:46:01 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command		*init_commands(size_t count);
static size_t			count_commands(char **tokens);
void					populate_commands(t_command *commands,
							char **tokens, size_t count);

t_command	*get_commands(char **tokens)
{
	t_command	*commands;
	size_t		count;

	commands = 0;
	count = count_commands(tokens);
	commands = init_commands(count);
	if (commands)
		populate_commands(commands, tokens, count);
	return (commands);
}

static size_t	count_commands(char **tokens)
{
	size_t	count;
	size_t	i;

	count = 1;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|')
			count++;
		i++;
	}
	return (count);
}

static t_command	*init_commands(size_t count)
{
	t_command	*commands;
	size_t		i;

	commands = (t_command *) malloc(sizeof (t_command) * (count + 1));
	if (!commands)
	{
		ft_error();
		return ((void *) 0);
	}
	i = 0;
	while (i < count + 1)
	{
		commands[i].args = 0;
		commands[i].redirections.r_stdin = 0;
		commands[i].redirections.r_stdout = 0;
		commands[i].redirections.heredoc = 0;
		commands[i].redirections.append = 0;
		commands[i].last = 0;
		i++;
	}
	commands[count].last = 1;
	return (commands);
}
