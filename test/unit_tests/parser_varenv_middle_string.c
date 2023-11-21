/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_varenv_end_string.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:36:39 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/17 11:55:08 by eguefif          ###   ########.fr       */
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
	char *tab = "\"salut $USER Hello\" echo salut";

	char *user = getenv("USER");
	char *tab_to_join[] = {"salut ", user, " Hello",  0};
	char *joinstr = ft_strjoin_tab(tab_to_join, "");
	char	*args1[] = {joinstr, "echo", "salut", 0};

	t_command cmd1 = {  .args = args1, 
						.redirections = { .r_stdin = 0, .r_stdout = 0}};
	t_command commands[] = {cmd1};

	test = ms_parser(tab,env); 
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
	printf("c1 stdin: %s\nc2 stdin: %s\n\n", c1.redirections.r_stdin, c2.redirections.r_stdin);

	printf("c1: %s\nc2: %s\n\n", c1.args[1], c2.args[1]);
	if (ft_strcmp(c1.args[1], c2.args[1]) != 0)
		return (1);
	printf("c1 stdin: %s\nc2 stdin: %s\n\n", c1.redirections.r_stdin, c2.redirections.r_stdin);

	printf("c1: %s\nc2: %s\n\n", c1.args[2], c2.args[2]);
	if (ft_strcmp(c1.args[2], c2.args[2]) != 0)
		return (1);
	printf("c1 stdin: %s\nc2 stdin: %s\n\n", c1.redirections.r_stdin, c2.redirections.r_stdin);

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
