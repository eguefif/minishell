/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:54:24 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/21 16:14:35 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	signal_init_c(void);
static void	signal_exec_c(int signal);

int	ms_init_signals(void)
{
	int	retval;

	retval = 0;
	if (!retval)
		retval = signal_init_c();
	return (retval);
}

static int	signal_init_c(void)
{
	struct sigaction	init_signal_c;

	sigemptyset(&init_signal_c.sa_mask);
	init_signal_c.sa_handler = signal_exec_c;
	if (sigaction(SIGINT, &init_signal_c, 0) == -1)
	{
		ft_error_message("SIGINT", SIGNAL_ERROR);
		return (1);
	}
	return (0);
}

static void	signal_exec_c(int signal)
{
	int	stat_loc;

	(void) signal;
	if (waitpid(-1, &stat_loc, WNOHANG) != 0)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
