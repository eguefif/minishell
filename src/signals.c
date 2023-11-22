/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:54:24 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/22 10:19:29 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signals_exec(int signal);

int	ms_reset_signals(void)
{
	struct sigaction	reset_signal;

	sigemptyset(&reset_signal.sa_mask);
	reset_signal.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &reset_signal, 0) == -1)
	{
		ft_error_message("SIGINT", SIGNAL_ERROR);
		return (1);
	}
	if (sigaction(SIGQUIT, &reset_signal, 0) == -1)
	{
		ft_error_message("SIGQUIT", SIGNAL_ERROR);
		return (1);
	}
	return (0);
}

int	ms_init_signals(void)
{
	struct sigaction	init_signal_c;
	struct sigaction	init_ignore;

	sigemptyset(&init_signal_c.sa_mask);
	init_signal_c.sa_handler = signals_exec;
	if (sigaction(SIGINT, &init_signal_c, 0) == -1)
	{
		ft_error_message("SIGINT", SIGNAL_ERROR);
		return (1);
	}
	init_ignore.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &init_ignore, 0) == -1)
	{
		ft_error_message("SIGQUIT", SIGNAL_ERROR);
		return (1);
	}
	return (0);
}

static void	signals_exec(int signal)
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
