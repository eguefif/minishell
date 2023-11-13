/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:42:06 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/13 18:35:06 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	non_interactive_mode(char **env);
void	interactive_mode(char **env);
int		check_valid_line_for_history(char *line);

int	main(int argc, char **argv, char **env)
{
	(void )argc;
	(void )argv;
	if (!isatty(0))
		non_interactive_mode(env);
	else if (isatty(0))
		interactive_mode(env);
	else
		ft_dprintf(2, "error: neither interactive nor non interactive\n");
}

void	non_interactive_mode(char **env)
{
	int		i;
	char	**commands;
	char	*line;

	i = 0;
	line = get_next_line(0);
	while (line)
	{
		commands = ms_parser(line);
		if (!commands && ft_strcmp(commands[0], "exit") == 0)
		{
			ms_cleanup(commands);
			break ;
		}
		else
			ms_execute(commands, env);
		ms_cleanup(commands);
		line = get_next_line(0);
	}
}

void	interactive_mode(char **env)
{
	char	*line;
	int		running;
	char	**commands;

	running = 1;
	while (running)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		if (check_valid_line_for_history(line))
			add_history(line);
		commands = ms_parser(line);
		if (ft_strcmp(commands[0], "exit") == 0)
			running = 0;
		else
			ms_execute(commands, env);
		ms_cleanup(commands);
	}
}

int	check_valid_line_for_history(char *line)
{
	if (ft_strlen(ft_strtrim(line, " \t")) != 0)
		return (1);
	return (0);
}
