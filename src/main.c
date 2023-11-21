/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:42:06 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/20 17:42:01 by eguefif          ###   ########.fr       */
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
	char	**ms_env;
	ms_env = init_env(env);
	if (!isatty(0))
		non_interactive_mode(ms_env);
	else if (isatty(0))
		interactive_mode(ms_env);
	else
		ft_dprintf(2, "error: neither interactive nor non interactive\n");
	ft_cleansplits(ms_env);
}

void	non_interactive_mode(char **env)
{
	int			i;
	t_command	*commands;
	char		*line;

	i = 0;
	line = get_next_line(0);
	while (line)
	{
		if (check_valid_line_for_history(line))
		{
			commands = ms_parser(line, env);
			if (errno == ENOMEM)
				break ;
			if (commands)
				ms_execute(commands, env);
			line = get_next_line(0);
		}
		if (line)
			free(line);
	}
}

void	interactive_mode(char **env)
{
	char		*line;
	int			running;
	t_command	*commands;

	running = 1;
	while (running)
	{
		line = readline(PROMPT);
		if (check_valid_line_for_history(line))
		{
			add_history(line);
			commands = ms_parser(line, env);
			if (errno == ENOMEM)
				break ;
			if (commands)
				ms_execute(commands, env);
			ms_clean_commands(commands);
		}
		if (line)
			free(line);
	}
}

int	check_valid_line_for_history(char *line)
{
	if (line && ft_strlen(ft_strtrim(line, " \t")) != 0)
		return (1);
	return (0);
}
