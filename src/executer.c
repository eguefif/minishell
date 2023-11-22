/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:43 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/22 12:27:30 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run(t_command *commands, char ***env);
static int	handle_child(t_command *commands, char **env);
static int	get_exit_code(int status);

int	ms_execute(t_command *commands, char ***env)
{
	int	stdin_save;
	int	stdout_save;
	int	retval;

	stdin_save = dup(0);
	stdout_save = dup(1);
	if (stdout_save == -1 || stdin_save == -1)
		return (ft_error());
	retval = run(commands, env);
	if (dup2(stdin_save, 0) == -1)
		return (ft_error());
	if (dup2(stdout_save, 1) == -1)
		return (ft_error());
	return (retval);
}

static int	run(t_command *commands, char ***env)
{
	int	pipe_fd[2];
	int	retval;
	int	pid;
	int	stat_loc;
	int	i;

	i = -1;
	pid = -1;
	while (!commands[++i].last)
	{
		retval = exec_builtin(commands[i], env);
		if (retval == -1)
		{
			if (pipe(pipe_fd) == -1)
				return (ft_error());
			pid = fork();
			if (pid < 0)
				return (ft_error());
			else if (!pid)
			{
				if (ms_reset_signals() != 0)
					return (1);
				if (set_redirections(commands[i], pipe_fd,
						commands[i + 1].last))
					return (1);
				if (!commands[i].args[0])
					return (0);
				ft_exit_nb(commands, handle_child(&commands[i], *env));
			}
			if (dup2(pipe_fd[0], 0) == -1)
				return (ft_error());
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
	}
	if (pid >= 0)
	{
		waitpid(pid, &stat_loc, 0);
		retval = get_exit_code(stat_loc);
		while (waitpid(-1, &stat_loc, 0) > 0)
			;
		ms_ignore_signals();
	}
	return (retval);
}

int	set_redirections(t_command command, int *pipe_fd, int last)
{
	int	fd;
	int	retval;

	retval = 0;
	if (command.redirections.r_stdin)
	{
		fd = open(command.redirections.r_stdin, O_RDONLY);
		if (fd < 0)
		{
			ft_error_message(command.redirections.r_stdin, OPEN_ERROR);
			retval = 1;
		}
		else
		{
			if (dup2(fd, 0) == -1)
				retval = ft_error();
		}
	}
	if (command.redirections.r_stdout)
	{
		if (!command.redirections.append)
		{
			fd = open(command.redirections.r_stdout,
					O_TRUNC | O_WRONLY | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
		else
		{
			fd = open(command.redirections.r_stdout,
					O_APPEND | O_WRONLY | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
		if (fd < 0)
		{
			ft_error_message(command.redirections.r_stdout, OPEN_ERROR);
			retval = 1;
		}
		else
		{
			if (dup2(fd, 1) == -1)
				retval = ft_error();
			close(fd);
		}
	}
	else if (last != 1)
	{
		if (dup2(pipe_fd[1], 1) == -1)
			retval = ft_error();
	}
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
		if (is_dir(path) > 0)
			ft_error_message(commands[0].args[0], IS_DIR);
		else
			ft_error_message(commands[0].args[0], NO_RIGHT);
		return (126);
	}
	if (!is_echo_or_env(path, env))
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
