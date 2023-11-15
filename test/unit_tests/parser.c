/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:40:57 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/15 13:01:11 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_command(t_command c1, t_command c2);

int	main()
{
	/*
	char *tab[] = {
		"echo \'salut \"je suis\" un test\'",
		"echo \"salut \'je suis\' u ntest\"",
		"echo test test \'salut \"je suis\'",
		"< file.txt cat -e | tail > output.txt",
		"cat -e",
		"<file.txt cat>file.txt",
		"<file.txt cat>file.txt|tail>output.x",
		"ls -ls",
		"/bin/ls",
		"/bin/ls\t\t\t\t      |        tail > output.txt -c 8",
		""
	};
	*/
	char *tab = "< file.txt cat -e | tail > output.x -c 8";
	char	*args1[] = {"cat", "-e", 0};
	t_command cmd1 = {  .args = args1, 
						.redirections = { .r_stdin = "file.txt", .r_stdout = 0}};
	char	*args2[] = {"tail", "-c", "8", 0};
	t_command cmd2 = {  .args = args2,
						.redirections = { .r_stdin = 0, .r_stdout = "output.txt" }};
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
	if (ft_strcmp(c1.redirections.r_stdin, c2.redirections.r_stdin) != 0)
		return (1);
	if (ft_strcmp(c1.redirections.r_stdout, c2.redirections.r_stdout) != 0)
		return (1);
	return (0);
}
