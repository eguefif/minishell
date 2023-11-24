/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:42:06 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/24 16:50:03 by eguefif          ###   ########.fr       */
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
	int		retval;
	char	*env_retval;

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
	env_retval = ms_getenv(ms_env, "?");
	retval = 0;
	if (env_retval)
	{
		retval = ft_atoi(env_retval);
		free(env_retval);
	}
	ft_cleansplits(ms_env);
	return (retval);
}

char	**non_interactive_mode(char **env)
{
	char		*line;
	t_command	*commands;
	int			retval;

	ms_set_terminal_attr();
	line = get_next_line(0);
	while (line)
	{
		retval = 0;
		if (ms_init_signals() != 0)
			break ;
		if (check_valid_line_for_history(line))
		{
			commands = ms_parser(line, env);
			if (line)
				free(line);
			if (commands && commands->args && commands->args[0] && commands->args[0] && ft_strcmp(commands->args[0], "exit") == 0)
			{
				if (commands->args[1])
				{
				   	 if (ft_is_strnum(commands->args[1]))
						retval = ft_atoi(commands->args[1]);
					 else
					 {
						 ft_error_message(commands->args[1], EXIT_NON_NUM);
						 retval = 255;
					 }
				}
				env = handle_exit_code(env, retval);
				ms_clean_commands(commands);
				break ;
			}
			if (errno == ENOMEM)
				break ;
			if (commands)
			{
				retval = ms_execute(commands, &env);
				env = handle_exit_code(env, retval);
			}
			else 
				env = handle_exit_code(env, 258);
			ms_clean_commands(commands);
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
	int			running;
	t_command	*commands;
	int			retval;

	ms_set_terminal_attr();
	running = 1;
	while (running)
	{
		retval = 0;
		if (ms_init_signals() != 0)
			break ;
		line = readline(PROMPT);
		if (check_valid_line_for_history(line))
		{
			add_history(line);
			commands = ms_parser(line, env);
			if (line)
				free(line);
			if (commands && commands->args && commands->args[0] && commands->args[0] && ft_strcmp(commands->args[0], "exit") == 0)
			{
				if (commands->args[1])
				{
				   	 if (ft_is_strnum(commands->args[1]))
						retval = ft_atoi(commands->args[1]);
					 else
					 {
						 ft_error_message(commands->args[1], EXIT_NON_NUM);
						 retval = 255;
					 }
				}
				env = handle_exit_code(env, retval);
				ms_clean_commands(commands);
				break ;
			}
			if (errno == ENOMEM)
				break ;
			if (commands)
			{
				retval = ms_execute(commands, &env);
				env = handle_exit_code(env, retval);
			}
			else 
				env = handle_exit_code(env, 258);
			ms_clean_commands(commands);
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
	char *tmp;

	if (!line)
		return (0);
	tmp = ft_strtrim(line, "\t ");
	if (line && tmp!= 0)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

char	**handle_mshlvl(char **env)
{
	int		mshlvl;
	char	*tmp;
	char	*var;

	if (is_var(env, "MSHLVL"))
	{
		var = ms_getenv(env, "MSHLVL");
		mshlvl = ft_atoi(var) + 1;
		free(var);
		tmp = ft_itoa(mshlvl);
		env = update_var(env, "MSHLVL", tmp);
		free(tmp);
		return (env);
	}
	mshlvl = 1;
	tmp = ft_itoa(mshlvl);
	env = add_var(env, "MSHLVL", tmp);
	free(tmp);
	return (env);
}

char	**handle_exit_code(char **env, int retval)
{
	char	*tmp_retval;

	tmp_retval = ft_itoa(retval);
	if (is_var(env, "?"))
		env = update_var(env, "?", tmp_retval);
	else 
		env = add_var(env, "?", tmp_retval);
	free(tmp_retval);
	return (env);
}
