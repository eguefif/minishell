/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:43 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/20 14:10:52 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int run(t_command *commands, char **env);
static int	handle_child(t_command *commands, char **env, int pipe_fd[]);
static int	get_exit_code(int status);

int	ms_execute(t_command *commands, char **env)
{
	int	stdin_save;
	int	stdout_save;
	int	retval;

	stdin_save = dup(0);
	stdout_save = dup(1);
	retval = run(commands, env);
	dup2(stdin_save, 0);
	dup2(stdout_save, 1);
	ft_printf("Return code : %d\n", retval);
	return (retval);
}

static int run(t_command *commands, char **env)
{
	int	pipe_fd[2];
	int	retval;
	int	stat_loc;
	int	i;

	i = -1;
	while (!commands[++i].last)
	{
		if (pipe(pipe_fd) == -1)
			return (1);
		retval = fork();
		if (retval < 0)
		{
			ft_error();
			return (1);
		}
		else if (!retval)
		{
			ft_exit_nb(commands, handle_child(&commands[i], env, pipe_fd));
		}
		if (dup2(pipe_fd[0], 0) == -1)
			return (1);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	waitpid(retval, &stat_loc, 0);
	retval = get_exit_code(stat_loc);
	while (waitpid(-1, &stat_loc, 0) > 0)
		;
	return (retval);
}

static int	handle_child(t_command *commands, char **env, int pipe_fd[])
{
	char	*path;

	path = get_command_path(commands[0].args[0], env);
	if (!path)
	{
		ft_error_message(commands[0].args[0], NO_FILE);
		return (127);
	}
	if (access(path, X_OK) != 0)
	{
		ft_error_message(commands[0].args[0], NO_RIGHT);
		return (126);
	}
	if (!commands[1].last)
		if (dup2(pipe_fd[1], 1) == -1)
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (execve(path, commands[0].args, env) == -1)
		ft_dprintf(2, "command %s\n", commands[0].args[0]);
	return (0);
}

static int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (1);
}
