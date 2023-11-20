/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:56:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/17 14:03:17 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(void)
{
	perror(PROG_NAME);
}

void	ft_error_message(char *s, int error_type)
{
	if (error_type == SYNTAX_ERROR)
		ft_dprintf(2, "%s: syntax error near unexpected token \'%s\'\n",
			PROG_NAME, s);
	if (error_type == NO_FILE)
		ft_dprintf(2, "%s: %s: no such file or directory%n", PROG_NAME, s);
	if (error_type == NO_RIGHT)
		ft_dprintf(2, "%s: %s: Permission denied\n", PROG_NAME, s);
}
