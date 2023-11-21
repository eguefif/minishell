/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:40:57 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/17 09:39:01 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_command(t_command c1, t_command c2);

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	t_command *test;
	int i = 0;
	char	*tab= "/bin/ls | e\"cho\" \"y\'ooo\"  | wc > file2 | ls < file1 | grep";


	char	*args1[] = {"/bin/ls", 0};
	t_command cmd1 = {  .args = args1, 
						.redirections = { .r_stdin = 0, .r_stdout = 0}};
	char	*args2[] = {"echo", "yooo", 0};
	t_command cmd2 = {  .args = args2, 
						.redirections = { .r_stdin = 0, .r_stdout = 0}};
	char	*args3[] = {"wc", 0};
	t_command cmd3 = {  .args = args3, 
						.redirections = { .r_stdin = 0, .r_stdout = "file2"}};
	char	*args4[] = {"ls", 0};
	t_command cmd4 = {  .args = args4, 
						.redirections = { .r_stdin = "file1", .r_stdout = 0}};
	char	*args5[] = {"grep", 0};
	t_command cmd5 = {  .args = args5, 
						.redirections = { .r_stdin = 0, .r_stdout = 0}};

	t_command commands[] = {cmd1, cmd2, cmd3, cmd4, cmd5};
	test = ms_parser(tab,env); 
	while (i < 5)
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
