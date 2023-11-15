/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:17:01 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/15 17:07:34 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command			*init_commands(size_t count);
static void 				populate_commands(t_command *commands,
								char **tokens, size_t count);
static size_t				get_argc(char **tokens);
static t_redirections		populate_redirection(t_redirections redir,
								char *token, char *file);
static size_t				count_commands(char **tokens);

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
	while(tokens[i])
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
		commands[i].args =  0;
		commands[i].redirections.r_stdin = 0;
		commands[i].redirections.r_stdout = 0;
		commands[i].last = 0;
		i++;
	}
	commands[count].last = 1;
	return (commands);
}

static void	populate_commands(t_command *commands,
				char **tokens, size_t count)
{
	size_t	i;
	size_t	argc;
	size_t	c_count;
	size_t	j;

	i = 0;
	c_count = 0;
	while (c_count < count)
	{
		argc = get_argc(tokens + i);
		commands[c_count].args = ft_calloc(sizeof (char *), argc + 1);
		commands[c_count].args[argc] = (void *) 0;
		while (tokens[i] && tokens[i][0] != '|')
		{
			if (tokens[i][0] == '<' || tokens[i][0] == '>')
			{
				commands[c_count].redirections = populate_redirection(
						commands[c_count].redirections, tokens[i], tokens[i + 1]);
				i += 2;
			}
			else
			{
				j = 0;
				while (commands[c_count].args[j])
					j++;
				commands[c_count].args[j] = ft_strdup(tokens[i]);
				i++;
			}
		}
		if (tokens[i] && tokens[i][0] == '|')
			i++;
		c_count++;
	}
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
		if (redir.r_stdin)
			free(redir.r_stdin);
		redir.r_stdin = ft_strdup(file);
		if (!redir.r_stdin)
			ft_error();
	}
	else if (token[0] == '>')
	{
		if (redir.r_stdout)
			free(redir.r_stdout);
		redir.r_stdout = ft_strdup(file);
		if (!redir.r_stdout)
			ft_error();
	}
	return (redir);
}
