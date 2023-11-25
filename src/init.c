/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 09:56:37 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/25 15:44:13 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**handle_mshlvl(char **env);

char	**init(char **env)
{
	char	**ms_env;

	ms_env = init_env(env);
	if (!is_var(env, "?"))
		ms_env = add_var(ms_env, "?", "0");
	else
		ms_env = update_var(ms_env, "?", "0");
	ms_env = handle_mshlvl(ms_env);
	return (ms_env);
}

int	terminate(char **ms_env)
{
	int		retval;
	char	*env_retval;

	env_retval = ms_getenv(ms_env, "?");
	retval = 0;
	if (env_retval)
	{
		retval = ft_atoi(env_retval);
		free(env_retval);
	}
	ft_cleansplits(ms_env);
	return (retval);
}

char	**handle_mshlvl(char **env)
{
	int		mshlvl;
	char	*tmp;
	char	*var;

	if (is_var(env, "MSHLVL"))
	{
		var = ms_getenv(env, "MSHLVL");
		mshlvl = ft_atoi(var) + 1;
		free(var);
		tmp = ft_itoa(mshlvl);
		env = update_var(env, "MSHLVL", tmp);
		free(tmp);
		return (env);
	}
	mshlvl = 1;
	tmp = ft_itoa(mshlvl);
	env = add_var(env, "MSHLVL", tmp);
	free(tmp);
	return (env);
}
