/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:43 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/25 15:25:44 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**builtin_unset(t_command cmd, char **env);
static int	builtin_cd(char *cmd, char ***env);
static void	handle_cd_no_path(char **env);

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

	if (is_dir(path) == -1)
		return (ft_error_message(path, CD_NO_FILE));
	else if (is_file(path))
		return (ft_error_message(path, CD_NOT_A_DIRECTORY));
	else if (!path)
		handle_cd_no_path(*env);
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

static void	handle_cd_no_path(char **env)
{
	char	*tmp;

	tmp = ms_getenv(env, "HOME");
	if (!tmp)
		chdir("/");
	else
	{
		chdir(tmp);
		free(tmp);
	}
}
