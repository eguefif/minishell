/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_commands_populate.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:22:53 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/23 13:55:47 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t			get_argc(char **tokens);
static t_redirections	populate_redirection(t_redirections redir,
							char *token, char *file);
static t_command		populate(t_command command, size_t *i, char **tokens);

void	populate_commands(t_command *commands,
				char **tokens, size_t count)
{
	size_t	i;
	size_t	argc;
	size_t	c_count;

	i = 0;
	c_count = 0;
	while (c_count < count)
	{
		argc = get_argc(tokens + i);
		commands[c_count].args = ft_calloc(sizeof (char *), argc + 1);
		while (tokens[i] && tokens[i][0] != '|')
			commands[c_count] = populate(commands[c_count], &i, tokens);
		if (tokens[i] && tokens[i][0] == '|')
			i++;
		c_count++;
	}
}

static t_command	populate(t_command command, size_t *i, char **tokens)
{
	int		j;

	if (tokens[*i][0] == '<' || tokens[*i][0] == '>')
	{
		command.redirections = populate_redirection(
				command.redirections,
				tokens[*i], tokens[*i + 1]);
		*i += 2;
	}
	else
	{
		j = 0;
		while (command.args[j])
			j++;
		command.args[j] = ft_strdup(tokens[*i]);
		*i += 1;
	}
	return (command);
}

size_t	get_argc(char **tokens)
{
	size_t	i;
	size_t	argc;

	i = 0;
	argc = 0;
	while (tokens[i] && tokens[i][0] != '|')
	{
		if (tokens[i][0] == '<' || tokens[i][0] == '>')
			i += 2;
		else
		{
			argc++;
			i++;
		}
	}
	return (argc);
}

static t_redirections	populate_redirection(t_redirections redir,
							char *token, char *file)
{
	if (token[0] == '<')
	{
		if (token[1] && token[1] == '<')
		{
			if (ft_strchr(token, '\"') || ft_strchr(token, '\''))
				redir.heredoc = 1;
			else
				redir.heredoc = 2;
		}
		if (redir.r_stdin)
			free(redir.r_stdin);
		redir.r_stdin = ft_strdup(file);
		if (!redir.r_stdin)
			ft_error();
	}
	else if (token[0] == '>')
	{
		if (token[1] == '>')
			redir.append = 1;
		if (redir.r_stdout)
			free(redir.r_stdout);
		redir.r_stdout = ft_strdup(file);
		if (!redir.r_stdout)
			ft_error();
	}
	return (redir);
}
