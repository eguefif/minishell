/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_simple_commands1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:24:14 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/17 11:56:49 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_command(t_command c1, t_command c2);

int	main(int argc, char **argv, char **env)
{
	(void) argv;
	(void) argc;
	t_command *test;
	char *tab = 0;

	test = ms_parser(tab,env); 
	if (test)
		printf("Error: Did not return void pointer");
}
