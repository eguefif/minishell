/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:43 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/25 11:25:32 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**builtin_unset(t_command cmd, char **env);
static int	builtin_cd(char *cmd, char ***env);

int	exec_builtin(t_command cmd, char ***env)
{
	if (ft_strcmp(cmd.args[0], "export") == 0)
		return (builtin_export(cmd, env));
	else if (ft_strcmp(cmd.args[0], "unset") == 0)
	{
		*env = builtin_unset(cmd, *env);
		return (0);
	}
	else if (ft_strcmp(cmd.args[0], "cd") == 0)
		return (builtin_cd(cmd.args[1], env));
	return (-1);
}

static char	**builtin_unset(t_command cmd, char **env)
{
	int	i;

	i = 1;
	while (cmd.args[i])
	{
		if (is_var(env, cmd.args[i]))
			env = remove_var(env, cmd.args[i]);
		i++;
	}
	return (env);
}

static int	builtin_cd(char *path, char ***env)
{
	char	cwd[257];
	char	*tmp;

	if (!path)
	{
		tmp = ms_getenv(*env, "HOME");
		chdir(tmp);
		free(tmp);
	}
	else
		chdir(path);
	if (getcwd(cwd, 257) == 0)
		return (1);
	if (is_var(*env, "PWD"))
		*env = update_var(*env, "PWD", cwd);
	else
		*env = add_var(*env, "PWD", cwd);
	return (0);
}
