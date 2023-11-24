/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:54:24 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/24 10:50:26 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_signal_c(int signal);
static void	exec_signal_heredoc(int signal);

int	ms_ignore_signals(void)
{
	struct sigaction	init_ignore;

	init_ignore.sa_mask = 0;
	init_ignore.sa_flags = 0;
	init_ignore.sa_handler = 0;
	sigemptyset(&init_ignore.sa_mask);
	init_ignore.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &init_ignore, 0) == -1)
	{
		ft_error_message("SIGINT", SIGNAL_ERROR);
		return (1);
	}
	if (sigaction(SIGQUIT, &init_ignore, 0) == -1)
	{
		ft_error_message("SIGQUIT", SIGNAL_ERROR);
		return (1);
	}
	return (0);
}

int	ms_reset_signals(void)
{
	struct sigaction	reset_signal;

	reset_signal.sa_mask = 0;
	reset_signal.sa_flags = 0;
	reset_signal.sa_handler = 0;
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

	init_signal_c.sa_mask = 0;
	init_signal_c.sa_flags = 0;
	init_signal_c.sa_handler = 0;
	init_ignore.sa_mask = 0;
	init_ignore.sa_flags = 0;
	init_ignore.sa_handler = 0;

	sigemptyset(&init_signal_c.sa_mask);
	init_signal_c.sa_handler = exec_signal_c;
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

static void	exec_signal_c(int signal)
{
	(void) signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
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

void	ms_set_terminal_attr(void)
{
	struct termios	termios_p;

	if (tcgetattr(0, &termios_p) == -1)
		return ;
	termios_p.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &termios_p);
}

