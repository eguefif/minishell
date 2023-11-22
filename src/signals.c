/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:54:24 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/22 09:39:26 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	signals_init(void);
static void	signals_exec(int signal);

int	ms_init_signals(void)
{
	int	retval;

	retval = 0;
	if (!retval)
		retval = signals_init();
	return (retval);
}

static int	signals_init(void)
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

	if (waitpid(-1, &stat_loc, WNOHANG) != 0 && signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
