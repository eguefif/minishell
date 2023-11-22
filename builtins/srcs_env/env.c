/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c						:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:36:39 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/22 13:08:44 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	main(int argc, char *argv[], char **env)
{
	(void) argc;
	(void) argv;
	int	i;

	i = 0;
	while (env[i])
		ft_printf("%s\n", env[i++]);
	return (0);
}
