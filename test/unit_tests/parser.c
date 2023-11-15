/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:40:57 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/14 16:19:30 by eguefif          ###   ########.fr       */
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
	t_command cmd1 = {  .args = {"cat", "-e", 0}, 
						.files = { .r_stdin = "file.txt", .r_stdout = 0}};
	t_command cmd2 = {  .args = {"tail", "-c", "8", 0}, 
						.files = { .r_stdin = 0, .r_stdout = "output.txt" }};
	t_command *commands = {cmd1, cmd2};

	i = 0;
	t_commands *test;
	test = ms_parser(tab); 
	while (commands[i])
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
	while (c1[i])
	{
		if (ft_strcmp(c1.args[i], c2.args[i]) != 0)
			return (1);
		i++;
	}
	if (ft_strcmp(c1.files.r_stdin, c2.files.r_stdin) != 0)
		return (1);
	if (ft_strcmp(c1.files.r_stdout, c2.files.r_stdout) != 0)
		return (1);
	return (0);
}
