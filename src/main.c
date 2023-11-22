/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:42:06 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/21 15:26:28 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	non_interactive_mode(char **env);
void	interactive_mode(char **env);
int		check_valid_line_for_history(char *line);
char	**handle_exit_code(char **env, int retval);		

int	main(int argc, char **argv, char **env)
{
	(void )argc;
	(void )argv;
	char	**ms_env;
	ms_env = init_env(env);
	ms_init_signals();
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
	int		retval;

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
			{
				retval = ms_execute(commands, env);
				env = handle_exit_code(env, retval);		
			}
			line = get_next_line(0);
			if (line)
				free(line);
		}
		else if (!line)
			return ;
	}
}

void	interactive_mode(char **env)
{
	char		*line;
	int		running;
	t_command	*commands;
	int		retval;

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
			return ;
		}
	}
}

int	check_valid_line_for_history(char *line)
{
	if (line && ft_strlen(ft_strtrim(line, " \t")) != 0)
		return (1);
	return (0);
}

char	**handle_exit_code(char **env, int retval)
{
	if (is_var(env, "?"))
		env = update_var(env, "?", ft_itoa(retval));
	else 
		env = add_var(env, "?", ft_itoa(retval));
	return (env);
}
