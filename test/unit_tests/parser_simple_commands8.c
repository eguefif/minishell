/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_simple_commands8.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:41:59 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/17 11:42:42 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_command(t_command c1, t_command c2);

int	main()
{
	t_command *test;
	int i = 0;
	char *tab = "echo -nnnnnn salut toi";

	char	*args1[] = {"echo", "-nnnnnn", "salut", "toi", 0};
	t_command cmd1 = {  .args = args1, 
						.redirections = { .r_stdin = 0, .r_stdout = 0}};
	t_command commands[] = {cmd1};

	test = ms_parser(tab); 
	while (i < 1)
	{
		if (cmp_command(test[i], commands[i]) == 1)
			ft_printf("Error\n");
		i++;
	}
}

int	cmp_command(t_command c1, t_command c2)
{
	printf("c1: %s\nc2: %s\n\n", c1.args[0], c2.args[0]);
	if (ft_strcmp(c1.args[0], c2.args[0]) != 0)
		return (1);
	printf("c1: %s\nc2: %s\n\n", c1.args[1], c2.args[1]);
	if (ft_strcmp(c1.args[1], c2.args[1]) != 0)
		return (1);
	printf("c1: %s\nc2: %s\n\n", c1.args[2], c2.args[2]);
	if (ft_strcmp(c1.args[2], c2.args[2]) != 0)
		return (1);
	printf("c1: %s\nc2: %s\n\n", c1.args[3], c2.args[3]);
	if (ft_strcmp(c1.args[3], c2.args[3]) != 0)
		return (1);
	printf("c1 stdin: %s\nc2 stdin: %s\n\n", c1.redirections.r_stdin, c2.redirections.r_stdin);
	if (!c1.redirections.r_stdin && !c2.redirections.r_stdin)
		ft_printf("no stdin\n");
	else if (ft_strcmp(c1.redirections.r_stdin, c2.redirections.r_stdin) != 0)
		return (1);

	printf("c1 stdout: %s\nc2 stdout: %s\n\n", c1.redirections.r_stdout, c2.redirections.r_stdout);
	if (!c1.redirections.r_stdout && !c2.redirections.r_stdout)
		ft_printf("no stdout\n");
	else if (ft_strcmp(c1.redirections.r_stdout, c2.redirections.r_stdout) != 0)
		return (1);
	return (0);
}
