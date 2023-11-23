/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:43 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/23 15:33:53 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**builtin_unset(t_command cmd, char **env);
static int	builtin_export(t_command cmd, char ***env);
static int	is_valid_identifier(char *id);
static int	builtin_cd(char *cmd, char ***env);
static int	builtin_pwd(void);
static int	builtin_env(char **env);
static int	builtin_echo(char **cmd);

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

static int	builtin_export(t_command cmd, char ***env)
{
	int	i;
	int	retval;
	char	**splits;

	i = 1;
	retval = 0;
	while (cmd.args[i])
	{
		if (is_valid_identifier(cmd.args[i]))
		{
			splits = ft_split(cmd.args[i], '=');
			if (is_var(*env, cmd.args[i]))
				*env = update_var(*env, splits[0], splits[1]);
			else
				*env = add_var(*env, splits[0], splits[1]);
			ft_cleansplits(splits);
		}
		else 
		{
			ft_error_message(cmd.args[i], EXPORT_ERROR);
			if (ft_strchr(cmd.args[i], '='))
				retval = 1;
		}
		i++;
	}
	return (retval);
}

static int	is_valid_identifier(char *id)
{
	int	i;

	if (!ft_strchr(id, '='))
		return (0);
	if (ft_isdigit(id[0]))
		return (0);
	i = 1;
	while (id[i] != '=')
	{
		if (!(ft_isalnum(id[i]) || id[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	builtin_cd(char *path, char ***env)
{
	char cwd[257];

	chdir(path);
	if (getcwd(cwd, 257) == 0)
		return (1);
	if (is_var(*env, "PWD"))
		*env = update_var(*env, "PWD", cwd);
	else
		*env = add_var(*env, "PWD", cwd);
	return (0);
}

static int	builtin_pwd(void)
{
	char cwd[257];

	if (getcwd(cwd, 257))
		ft_printf("%s\n",  cwd);
	else 
		return (0);
	return (1);
}

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
		return(builtin_pwd());
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
	int	i;
	char	*end;

	end = "\n";
	i = 1;
	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] == 'n' && ft_strlen(cmd[1]) == 2)
		i = 2;
	while (cmd[i])
	{
		ft_printf("%s", cmd[i]);
		if (cmd[i + 1])
			ft_printf(" ");
		i++;
	}
	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] == 'n' && ft_strlen(cmd[1]) == 2)
		ft_printf("");
	else 
		ft_printf("\n");
	return (1);
}
