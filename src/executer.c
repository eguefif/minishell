/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:43 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/25 12:14:57 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run(t_command *commands, char ***env);
static int	get_exit_code(int status);
static int	parent_wait(int pid);

// In executer_fork.c
int			execute_fork(t_command *commands, int i, char ***env, int *pid);

int	ms_execute(t_command *commands, char ***env)
{
	int	stdin_save;
	int	stdout_save;
	int	retval;

	stdin_save = dup(0);
	stdout_save = dup(1);
	if (stdout_save == -1 || stdin_save == -1)
		return (ft_error());
	commands = builtin_heredoc(commands, *env);
	retval = run(commands, env);
	builtin_heredoc_delete(commands);
	if (dup2(stdin_save, 0) == -1)
		return (ft_error());
	if (dup2(stdout_save, 1) == -1)
		return (ft_error());
	return (retval);
}

static int	run(t_command *commands, char ***env)
{
	int	retval;
	int	pid;
	int	i;

	i = -1;
	pid = -1;
	while (!commands[++i].last)
	{
		retval = exec_builtin(commands[i], env);
		if (retval == -1)
			if (execute_fork(commands, i, env, &pid))
				return (1);
	}
	if (pid >= 0)
		retval = parent_wait(pid);
	return (retval);
}

static int	parent_wait(int pid)
{
	int	retval;
	int	stat_loc;

	ms_ignore_signals();
	waitpid(pid, &stat_loc, 0);
	retval = get_exit_code(stat_loc);
	while (waitpid(-1, &stat_loc, 0) > 0)
		;
	return (retval);
}

static int	get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (1);
}
