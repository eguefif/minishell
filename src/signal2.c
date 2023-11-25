/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:30:35 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/25 11:34:51 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_signal_heredoc(int signal);

void	ms_set_terminal_attr(void)
{
	struct termios	termios_p;

	if (tcgetattr(0, &termios_p) == -1)
		return ;
	termios_p.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &termios_p);
}

int	ms_heredoc_signals(void)
{
	struct sigaction	heredoc_signal;

	heredoc_signal.sa_mask = 0;
	heredoc_signal.sa_flags = 0;
	heredoc_signal.sa_handler = 0;
	sigemptyset(&heredoc_signal.sa_mask);
	heredoc_signal.sa_handler = exec_signal_heredoc;
	if (sigaction(SIGINT, &heredoc_signal, 0) == -1)
	{
		ft_error_message("SIGINT", SIGNAL_ERROR);
		return (1);
	}
	return (0);
}

static void	exec_signal_heredoc(int signal)
{
	(void) signal;
	write(1, "\n", 1);
}
