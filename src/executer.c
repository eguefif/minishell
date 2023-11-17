/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:43 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/17 13:38:21 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_execute(t_command *commands, char **env)
{
	int	retval;
	int	stat_loc;

	retval = fork();
	if (retval == 0)
	{
		if (execve(commands[0].args[0], commands[0].args, env) == -1)
		{
			exit (1);
		}
	}
	waitpid(retval, &stat_loc, 0);
	return (0);
}
