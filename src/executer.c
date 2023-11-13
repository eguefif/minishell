/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:43 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/13 18:34:40 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_execute(char **commands, char **env)
{
	int	retval;
	int	stat_loc;

	retval = fork();
	if (retval == 0)
	{
		if (execve(commands[0], commands, env) == -1)
		{
			if (DEBUG_MODE)
				ft_dprintf(1, "Error: Execve: %s %s\n",
					strerror(errno), commands[0]);
			ft_cleansplits(commands);
			exit (1);
		}
	}
	waitpid(retval, &stat_loc, 0);
	return (0);
}
