/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:42:06 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/25 10:51:54 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**non_interactive_mode(char **env);
char	**interactive_mode(char **env);
int		check_valid_line_for_history(char *line);
char	**handle_line(char *line, char **env);

int	main(int argc, char **argv, char **env)
{
	char	**ms_env;
	int		retval;

	(void)argc;
	(void)argv;
	ms_env = init(env);
	if (!isatty(0))
		ms_env = non_interactive_mode(ms_env);
	if (isatty(0))
		ms_env = interactive_mode(ms_env);
	else
		ft_dprintf(2, "error: neither interactive nor non interactive\n");
	retval = terminate(ms_env);
	return (retval);
}

char	**non_interactive_mode(char **env)
{
	char		*line;

	ms_set_terminal_attr();
	line = get_next_line(0);
	while (line)
	{
		if (ms_init_signals() != 0)
			break ;
		if (line)
		{
			env = handle_line(line, env);
			if (errno == ENOMEM)
				break ;
		}
		else if (!line)
		{
			ft_printf("exit\n");
			break ;
		}
		line = get_next_line(0);
	}
	return (env);
}

char	**interactive_mode(char **env)
{
	char		*line;
	int			retval;

	ms_set_terminal_attr();
	while (1)
	{
		retval = 0;
		if (ms_init_signals() != 0)
			break ;
		line = readline(PROMPT);
		if (check_valid_line_for_history(line))
		{
			add_history(line);
			env = handle_line(line, env);
		}
		else if (!line)
		{
			ft_printf("exit\n");
			break ;
		}
	}
	return (env);
}

char	**handle_line(char *line, char **env)
{
	int			retval;
	t_command	*commands;

	commands = ms_parser(line, env);
	if (line)
		free(line);
	if (errno == ENOMEM)
	{
		ms_clean_commands(commands);
		return (env);
	}
	if (commands)
	{
		builtin_exit(commands, &env);
		retval = ms_execute(commands, &env);
		env = handle_exit_code(env, retval);
	}
	else 
		env = handle_exit_code(env, 258);
	ms_clean_commands(commands);
	return (env);
}

int	check_valid_line_for_history(char *line)
{
	char	*tmp;

	if (!line)
		return (0);
	tmp = ft_strtrim(line, "\t \n");
	if (line && tmp && tmp[0])
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
