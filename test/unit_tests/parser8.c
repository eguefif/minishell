/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:40:57 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/17 09:39:27 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_command(t_command c1, t_command c2);
char *get_user_env(char **env);

int	main(int argc, char **argv, char **env)
{
	(void) argv;
	(void) argc;
	t_command *test;
	char *user = get_user_env(env);
	int i = 0;
	char	*tab= "echo $USER";

	char	*args1[] = {"echo", user,  0};
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
	free(user);
}

int	cmp_command(t_command c1, t_command c2)
{
	printf("c1: %s\nc2: %s\n\n", c1.args[0], c2.args[0]);
	if (ft_strcmp(c1.args[0], c2.args[0]) != 0)
		return (1);
	printf("c1 stdin: %s\nc2 stdin: %s\n\n", c1.redirections.r_stdin, c2.redirections.r_stdin);

	if (ft_strcmp(c1.args[1], c2.args[1]) != 0)
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

char *get_user_env(char **env)
{
	int	i = 0;

	while (env[i])
	{
		if (ft_strstr(env[i], "USER"))
			break ;
		i++;
	}

	char **split = ft_split(env[i], '=');
	char *user = ft_strdup(split[1]);
	ft_printf("%s\n", user);
	ft_cleansplits(split);
	return (user);
}
