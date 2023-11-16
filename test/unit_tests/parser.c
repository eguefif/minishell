/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:40:57 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/16 16:39:01 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_command(t_command c1, t_command c2);

int	main()
{
	char *tab = "< file.txt cat -e | tail > output.x -c 8";
	char	*args1[] = {"cat", "-e", 0};
	t_command cmd1 = {  .args = args1, 
						.redirections = { .r_stdin = "file.txt", .r_stdout = 0}};
	char	*args2[] = {"tail", "-c", "8", 0};
	t_command cmd2 = {  .args = args2,
						.redirections = { .r_stdin = 0, .r_stdout = "output.x" }};
	t_command commands[] = {cmd1, cmd2};

	int i = 0;
	t_command *test;
	test = ms_parser(tab); 
	while (i < 2)
	{
		if (cmp_command(test[i], commands[i]) == 1)
			ft_printf("Error\n");
		i++;
	}
}

int	cmp_command(t_command c1, t_command c2)
{
	int		i;

	i = 0;
	while (c1.args[i])
	{
		printf("c1: %s\nc2: %s\n\n", c1.args[i], c2.args[i]);
		if (ft_strcmp(c1.args[i], c2.args[i]) != 0)
			return (1);
		i++;
	}
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
