/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:40:07 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/20 17:36:01 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_getenv(char **env, char *var)
{
	int		i;
	size_t	len;
	char	*retval;
	char	**split;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0)
		{
			split = ft_split(env[i], '=');
			retval = ft_strdup(split[1]);
			ft_cleansplits(split);
			return (retval);
		}
		i++;
	}
	return (0);
}

char	**init_env(char **env)
{
	char	**retval;
	size_t	size;
	int	i;

	size = 0;
	while (env[size])
		size++;
	retval = (char **) malloc(sizeof(char **) * (size + 1));
	retval[size] = 0;
	i = 0;
	while (env[i])
	{
		retval[i] = ft_strdup(env[i]);
		i++;
	}
	return (retval);
}
