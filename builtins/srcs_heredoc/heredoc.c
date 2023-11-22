/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:36:39 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/22 15:50:01 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

int	main(int argc, char *argv[])
{
	char	*filename;
	char	**env;
	char	*end_line;

	(void) argc;
	filename = argv[1];
	end_line = argv[2];
	env = argv[3];

	return (0);
}
