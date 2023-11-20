/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:43 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/20 13:24:57 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_pipes(t_command *commands, char **env);

int	ms_execute(t_command *commands, char **env)
{
	int	retval;
	int	stat_loc;

	retval = fork();
	if (!retval)
		handle_pipes(commands, env);
	while (1)
		sleep(1);
	return (0);
}

static void handle_pipes(t_command *commands, char **env)
{
	int	pipe_fd[2];
	int	retval;
	int	stat_loc;
	int	i;

	i = 0;
	while (!commands[i].last)
	{
		if (commands[i + 1].last)
		{
			retval = fork();
			if (!retval)
			{
				if (execve(commands[i].args[0], commands[i].args, env) == -1)
				{
					ft_dprintf(2, "command %d\n", i);
					ft_exit(commands);
				}
			}
			else
			{
				wait(&stat_loc);
				exit(0);
			}
		}
		pipe(pipe_fd);
		retval = fork();
		if (!retval)
		{
			dup2(pipe_fd[0], 0);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			i++;
		}
		else
		{
			dup2(pipe_fd[1], 1);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			if (execve(commands[i].args[0], commands[i].args, env) == -1)
			{
				ft_dprintf(2, "command %d\n", i);
				ft_exit(commands);
			}
		}
	}
}
