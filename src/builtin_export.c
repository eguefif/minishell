/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:06:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/25 14:16:28 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**export(char *var, char **env);
static int	print_env(char **env);
static int	handle_error_export(char *var, int error);
static int	is_valid_identifier(char *id);

int	builtin_export(t_command cmd, char ***env)
{
	int		i;
	int		retval;
	int		error;

	retval = 0;
	if (cmd.args && !cmd.args[1])
		return (print_env(*env));
	i = 1;
	while (cmd.args && cmd.args[i])
	{
		error = is_valid_identifier(cmd.args[i]);
		if (error == -2)
			return (0);
		if (!error)
			*env = export(cmd.args[i], *env);
		else 
			retval = handle_error_export(cmd.args[i], error);
		i++;
	}
	return (retval);
}

static int	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("declare -x %s\n", env[i]);
		i++;
	}
	return (0);
}

static char	**export(char *var, char **env)
{
	char	**splits;

	splits = ft_split(var, '=');
	if (splits && splits[0] && splits[1])
	{
		if (splits[0] && splits[1] && is_var(env, splits[0]))
			env = update_var(env, splits[0], splits[1]);
		else
			env = add_var(env, splits[0], splits[1]);
		ft_cleansplits(splits);
	}
	return (env);
}

static int	handle_error_export(char *var, int error)
{
	if (error > 0)
		ft_error_message(var, EXPORT_ERROR);
	else
		ft_error_message(var, NO_EQUAL_IN_EXPORT);
	return (1);
}

static int	is_valid_identifier(char *id)
{
	int	i;

	if (!id)
		return (-2);
	if (!ft_strchr(id, '='))
		return (-1);
	if (ft_isdigit(id[0]))
		return (1);
	i = 1;
	while (id[i] != '=')
	{
		if (!(ft_isalnum(id[i]) || id[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}
