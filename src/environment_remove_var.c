/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_remove_var.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:43:04 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/25 11:52:24 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_size_env(char **env);

char	**remove_var(char **env, char *var)
{
	char	**retval;
	size_t	size;
	size_t	i;
	size_t	j;
	char	*cmp;

	i = -1;
	j = -1;
	if (!is_var(env, var))
		return (env);
	size = get_size_env(env);
	retval = (char **) ft_calloc(sizeof(char *), size);
	if (!retval)
		return (env);
	retval[size - 1] = 0;
	cmp = ft_strjoin(var, "=");
	while (++i < size)
	{
		if (ft_strstr(env[i], cmp) != env[i])
			retval[++j] = ft_strdup(env[i]);
	}
	free(cmp);
	ft_cleansplits(env);
	return (retval);
}

static size_t	get_size_env(char **env)
{
	size_t	retval;

	retval = 0;
	while (env[retval])
		retval++;
	return (retval);
}
