/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:10:46 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/15 13:14:07 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*get_commands(char **tokens);
size_t				count_commands(char **tokens);
t_command			*init_commands(size_t count);
void	populate_commands(t_command *commands, char **tokens, size_t count);
size_t	get_argc(char **tokens);
void	populate_redirection(t_redirections *redir, char *token, char *file);

t_command	*ms_parser(char *line)
{
	char		**tokens;
	t_command	*commands;

	tokens = ms_lexer(line);
	commands = get_commands(tokens);
	ms_clean_tokens(tokens);
	return (commands);
}

static t_command	*get_commands(char **tokens)
{
	t_command	*commands;
	size_t		count;

	count = count_commands(tokens);
	commands = init_commands(count);
	if (commands)
		populate_commands(commands, tokens, count);
	return (commands);
}

size_t	count_commands(char **tokens)
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

t_command	*init_commands(size_t count)
{
	t_command	*commands;

	commands = (t_command *) malloc(sizeof (t_command) * (count + 1));
	if (!commands)
	{
		ft_error();
		return ((void *) 0);
	}
	while (count > 0)
	{
		commands[count].args = (void *) 0;
		commands[count].redirections.r_stdin = (void *) 0;
		commands[count].redirections.r_stdout = (void *) 0;
		count--;
	}
	return (commands);
}

void	populate_commands(t_command *commands, char **tokens, size_t count)
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
		commands[c_count].args = malloc (sizeof (char *) * argc + 1);
		commands[c_count].args[argc] = (void *) 0;
		while (tokens[i] && tokens[i][0] != '|')
		{
			if (tokens[i][0] == '<' || tokens[i][0] == '>')
			{
				populate_redirection(&(commands[c_count].redirections),
						tokens[i], tokens[i + 1]);
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
		if (tokens[i][0] == '|')
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

void	populate_redirection(t_redirections *redir, char *token, char *file)
{
	if (token[0] == '<')
	{
		if (redir->r_stdin)
			free(redir->r_stdin);
		redir->r_stdin = ft_strdup(file);
		if (!redir->r_stdin)
			ft_error();
	}
	else if (token[0] == '>')
	{
		if (redir->r_stdout)
			free(redir->r_stdout);
		redir->r_stdout = ft_strdup(file);
		if (!redir->r_stdout)
			ft_error();
	}
}
