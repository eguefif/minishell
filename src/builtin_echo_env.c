/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:23:30 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/25 11:25:32 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtin_env(char **env);
static int	builtin_echo(char **cmd);
static int	builtin_pwd(void);

int	is_echo_or_env(char **cmd, char **env)
{
	int	retval;

	retval = 0;
	if (ft_strcmp(cmd[0], "env") == 0)
	{
		builtin_env(env);
		retval = 1;
	}
	else if (ft_strcmp(cmd[0], "echo") == 0)
	{
		retval = 1;
		builtin_echo(cmd);
	}
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (builtin_pwd());
	return (retval);
}

static int	builtin_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		ft_printf("%s\n", env[i++]);
	return (0);
}

static int	builtin_echo(char **cmd)
{
	int		i;
	char	*end;

	end = "\n";
	i = 1;
	if (cmd[1] && cmd[1][0] == '-'
			&& cmd[1][1] == 'n'
			&& ft_strlen(cmd[1]) == 2)
		i = 2;
	while (cmd[i])
	{
		ft_printf("%s", cmd[i]);
		if (cmd[i + 1])
			ft_printf(" ");
		i++;
	}
	if (cmd[1] && cmd[1][0] == '-'
			&& cmd[1][1] == 'n'
			&& ft_strlen(cmd[1]) == 2)
		ft_printf("");
	else 
		ft_printf("\n");
	return (1);
}

static int	builtin_pwd(void)
{
	char	cwd[257];

	if (getcwd(cwd, 257))
		ft_printf("%s\n", cwd);
	else 
		return (0);
	return (1);
}
