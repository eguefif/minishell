/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:43 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/20 17:37:49 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int run(t_command *commands, char **env);
static int	handle_child(t_command *commands, char **env);
static int	get_exit_code(int status);
static int	set_redirections(t_command command, int *pipe_fd);

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
			if (set_redirections(commands[i], pipe_fd))
				return (1);
			ft_exit_nb(commands, handle_child(&commands[i], env));
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

static int	set_redirections(t_command command, int *pipe_fd)
{
	int	fd;
	int	retval;

	retval = 0;
	if (command.redirections.r_stdin)
	{
		fd = open(command.redirections.r_stdin, O_RDONLY);
		if (fd < 0)
			ft_error_message(command.redirections.r_stdin, NO_FILE);
		else
		{
			if (dup2(fd, 0) == -1)
				retval = 1;
			close(fd);
		}
	}
	if (command.redirections.r_stdout)
	{
		fd = open(command.redirections.r_stdout, O_TRUNC | O_WRONLY | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
		if (fd < 0)
			ft_error_message(command.redirections.r_stdout, NO_FILE);
		else
		{
			if (dup2(fd, 1) == -1)
				retval = 1;
			close(fd);
		}
	}
	else if (dup2(pipe_fd[1], 1) == -1)
		retval = 1;
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (retval);
}

static int	handle_child(t_command *commands, char **env)
{
	char	*path;

	path = get_command_path(commands[0].args[0], env);
	if (!path)
	{
		ft_error_message(commands[0].args[0], NO_FILE);
		return (127);
	}
	if ((access(path, X_OK) != 0) || (is_dir(path) != 0))
	{
		if (is_dir(path) != 0)
			ft_error_message(commands[0].args[0], IS_DIR);
		else
			ft_error_message(commands[0].args[0], NO_RIGHT);
		return (126);
	}
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
