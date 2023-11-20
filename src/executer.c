/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:43 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/20 14:28:43 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_pipes(t_command *commands, char **env);

int	ms_execute(t_command *commands, char **env)
{
	int	retval;

	retval = fork();
	if (!retval)
		handle_pipes(commands, env);
	return (0);
}

static void handle_pipes(t_command *commands, char **env)
{
	int	pipe_fd[2];
	int	retval;
	int	stat_loc;
	int	i;
	int	stdin_save;
	int	stdout_save;

	i = 0;
	stdin_save = dup(0);
	stdout_save = dup(1);
	while (!commands[i].last)
	{
		pipe(pipe_fd);
		retval = fork();
		if (!retval)
		{
			if (!commands[i + 1].last)
				dup2(pipe_fd[1], 1);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			if (execve(commands[i].args[0], commands[i].args, env) == -1)
			{
				ft_dprintf(2, "command %d\n", i);
				ft_exit(commands);
			}
		}
		else
		{
			dup2(pipe_fd[0], 0);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			i++;
		}
	}
	while (waitpid(-1, &stat_loc, 0) > 0)
		;
	dup2(stdin_save, 0);
	dup2(stdout_save, 1);
}
