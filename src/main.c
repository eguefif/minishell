/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:42:06 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/22 12:19:12 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**non_interactive_mode(char **env);
char	**interactive_mode(char **env);
int		check_valid_line_for_history(char *line);
char	**handle_exit_code(char **env, int retval);		
char	**handle_mshlvl(char **env);

int	main(int argc, char **argv, char **env)
{
	char	**ms_env;

	(void)argc;
	(void)argv;
	ms_env = init_env(env);
	ms_env = handle_mshlvl(ms_env);
	if (!isatty(0))
		ms_env = non_interactive_mode(ms_env);
	else if (isatty(0))
		ms_env = interactive_mode(ms_env);
	else
		ft_dprintf(2, "error: neither interactive nor non interactive\n");
	ft_cleansplits(ms_env);
}

char	**non_interactive_mode(char **env)
{
	t_command	*commands;
	char		*line;
	int			retval;

	line = get_next_line(0);
	while (line)
	{
		if (check_valid_line_for_history(line))
		{
			commands = ms_parser(line, env);
			if (errno == ENOMEM)
				break ;
			if (commands)
			{
				retval = ms_execute(commands, env);
				env = handle_exit_code(env, retval);
			}
			line = get_next_line(0);
			if (line)
				free(line);
		}
		else if (!line)
			break ;
	}
	return (env);
}

char	**interactive_mode(char **env)
{
	char		*line;
	int			running;
	t_command	*commands;
	int			retval;

	running = 1;
	while (running)
	{
		if (ms_init_signals() != 0)
			break ;
		line = readline(PROMPT);
		if (check_valid_line_for_history(line))
		{
			add_history(line);
			commands = ms_parser(line, env);
			if (errno == ENOMEM)
				break ;
			if (commands)
			{
				retval = ms_execute(commands, env);
				env = handle_exit_code(env, retval);
			}
			else 
				env = handle_exit_code(env, 258);
			ms_clean_commands(commands);
			if (line)
				free(line);
		}
		else if (!line)
		{
			ft_printf("exit\n");
			break ;
		}
	}
	return (env);
}

int	check_valid_line_for_history(char *line)
{
	if (line && ft_strlen(ft_strtrim(line, " \t")) != 0)
		return (1);
	return (0);
}

char	**handle_mshlvl(char **env)
{
	int	mshlvl;

	if (is_var(env, "MSHLVL"))
	{
		mshlvl = ft_atoi(ms_getenv(env, "MSHLVL")) + 1;
		env = update_var(env, "MSHLVL", ft_itoa(mshlvl));
		return (env);
	}
	mshlvl = 1;
	env = add_var(env, "MSHLVL", ft_itoa(mshlvl));
	return (env);
}

char	**handle_exit_code(char **env, int retval)
{
	if (is_var(env, "?"))
		env = update_var(env, "?", ft_itoa(retval));
	else 
		env = add_var(env, "?", ft_itoa(retval));
	return (env);
}
