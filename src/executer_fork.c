/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:08:40 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/25 13:37:35 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_child(t_command *commands, int i, int *pipe_fd, char ***env);
static int	set_redirections(t_command command, int *pipe_fd, int last);
static int	set_redirection_stdout(t_command command);
static int	handle_child(t_command *commands, char **env);

int	execute_fork(t_command *commands, int i, char ***env, int *pid)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (ft_error());
	*pid = fork();
	if (*pid < 0)
		return (ft_error());
	else if (!*pid)
		run_child(commands, i, pipe_fd, env);
	if (dup2(pipe_fd[0], 0) == -1)
		return (ft_error());
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (0);
}

static void	run_child(t_command *commands, int i, int *pipe_fd, char ***env)
{
	int	retval;

	if (ms_reset_signals() != 0)
	{
		ms_clean_commands(commands);
		ft_cleansplits(*env);
		exit (1);
	}
	retval = set_redirections(commands[i], pipe_fd, commands[i + 1].last);
	if (retval)
	{
		ms_clean_commands(commands);
		ft_cleansplits(*env);
		exit(retval);
	}
	if (!commands[i].args[0])
	{
		ms_clean_commands(commands);
		ft_cleansplits(*env);
		exit (0);
	}
	ft_exit_nb(commands, handle_child(&commands[i], *env), *env);
}

int	set_redirections(t_command command, int *pipe_fd, int last)
{
	int	fd;
	int	retval;

	retval = 0;
	if (command.redirections.r_stdout)
		retval = (set_redirection_stdout(command));
	else if (last != 1)
	{
		if (dup2(pipe_fd[1], 1) == -1)
			retval = ft_error();
	}
	if (command.redirections.r_stdin)
	{
		fd = open(command.redirections.r_stdin, O_RDONLY);
		if (fd < 0)
			retval = ft_error_message(command.redirections.r_stdin, OPEN_ERROR);
		else
			if (dup2(fd, 0) == -1)
				retval = ft_error();
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (retval);
}

static int	set_redirection_stdout(t_command command)
{
	int	retval;
	int	fd;

	retval = 0;
	if (!command.redirections.append)
		fd = open(command.redirections.r_stdout,
				O_TRUNC | O_WRONLY | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd = open(command.redirections.r_stdout,
				O_APPEND | O_WRONLY | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		retval = ft_error_message(command.redirections.r_stdout, OPEN_ERROR);
	else
	{
		if (dup2(fd, 1) == -1)
			retval = ft_error();
		close(fd);
	}
	return (retval);
}

static int	handle_child(t_command *commands, char **env)
{
	char	*path;

	if (!(commands->args[0] && commands->args[0][0]))
	{
		ft_error_message(commands->args[0], COMMAND_NOT_FOUND);
		return (127);
	}
	if (!is_echo_or_env(commands[0].args, env))
	{
		path = get_command_path(commands[0].args[0], env);
		if (!path)
			return (127);
		if ((access(path, X_OK) != 0) || (is_dir(path) != 0))
		{
			if (is_dir(path) > 0)
				ft_error_message(commands[0].args[0], IS_DIR);
			else
				ft_error_message(commands[0].args[0], NO_RIGHT);
			return (126);
		}
		if (execve(path, commands[0].args, env) == -1)
			ft_dprintf(2, "command %s\n", commands[0].args[0]);
	}
	return (0);
}
