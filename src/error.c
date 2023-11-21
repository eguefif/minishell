/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:56:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/21 14:14:54 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(void)
{
	perror(PROG_NAME);
	return (1);
}

void	ft_error_message(char *s, int error_type)
{
	if (error_type == SYNTAX_ERROR)
		ft_dprintf(2, "%s: syntax error near unexpected token \'%s\'\n",
			PROG_NAME, s);
	else if (error_type == NO_FILE)
		ft_dprintf(2, "%s: %s: no such file or directory%n", PROG_NAME, s);
	else if (error_type == NO_RIGHT)
		ft_dprintf(2, "%s: %s: Permission denied\n", PROG_NAME, s);
	else if (error_type == IS_DIR)
		ft_dprintf(2, "%s: %s: is a directory\n", PROG_NAME, s);
	else if (error_type == OPEN_ERROR || error_type == SIGNAL_ERROR)
		ft_dprintf(2, "%s: %s: %s\n", PROG_NAME, s, strerror(errno));
}
