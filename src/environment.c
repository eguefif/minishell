/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:40:07 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/25 15:25:44 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_var(char **env, char *var);

char	*ms_getenv(char **env, char *var)
{
	int		i;
	size_t	len;
	char	*retval;
	char	**splits;
	char	*tmp;

	i = 0;
	len = ft_strlen(var);
	tmp = ft_strjoin(var, "=");
	while (env[i])
	{
		if (ft_strstr(env[i], tmp) == env[i])
		{
			splits = ft_split(env[i], '=');
			retval = ft_strdup(splits[1]);
			ft_cleansplits(splits);
			free(tmp);
			return (retval);
		}
		i++;
	}
	free(tmp);
	return (0);
}

char	**init_env(char **env)
{
	char	**retval;
	size_t	size;
	int		i;

	size = 0;
	while (env[size])
		size++;
	retval = (char **) ft_calloc(sizeof(char **), (size + 1));
	if (!retval)
		return (env);
	retval[size] = 0;
	i = 0;
	while (env[i])
	{
		retval[i] = ft_strdup(env[i]);
		i++;
	}
	return (retval);
}

char	**add_var(char **env, char *name, char *content)
{
	char	**retval;
	size_t	size;
	size_t	i;
	char	*tab[3];

	size = 0;
	while (env[size])
		size++;
	retval = (char **) ft_calloc(sizeof(char *), (size + 2));
	if (!retval)
		return (env);
	retval[size + 1] = 0;
	tab[0] = name;
	tab[1] = content;
	tab[2] = 0;
	retval[size] = ft_strjoin_tab(tab, "=");
	i = 0;
	while (i < size)
	{
		retval[i] = ft_strdup(env[i]);
		i++;
	}
	ft_cleansplits(env);
	return (retval);
}

char	**update_var(char **env, char *var, char *new_content)
{
	env = remove_var(env, var);
	env = add_var(env, var, new_content);
	return (env);
}

int	is_var(char **env, char *var)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(var, "=");
	while (env[i] && ft_strnstr(env[i], tmp, ft_strlen(tmp)) == 0)
		i++;
	free(tmp);
	if (env[i])
		return (1);
	return (0);
}
