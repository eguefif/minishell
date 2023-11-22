/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:43 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/22 10:24:48 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**builtin_unset(t_command cmd, char **env);

int	exec_builtin(t_command cmd, char ***env)
{
	if (ft_strcmp(cmd.args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd.args[0], "unset") == 0)
	{
		*env = builtin_unset(cmd, *env);
		return (1);
	}
	return (0);
}

static char	**builtin_unset(t_command cmd, char **env)
{
	int	i;

	i = 1;
	while (cmd.args[i])
	{
		ft_printf("%s\n", cmd.args[1]);
		if (is_var(env, cmd.args[i]))
			env = remove_var(env, cmd.args[i]);
		i++;
	}
	i = 0;
	return (env);
}
