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

char		**add_var(char **env, char *name, char *content)
{
	char	**retval;
	size_t	size;
	int	i;
	char	*tab[3];

	size = 0;
	while (env[size])
		size++;
	retval = (char **) malloc(sizeof(char *) * (size + 2));
	retval[size + 1] = 0;
	tab[0] = name;
	tab[1] = content;
	tab[2] = 0;
	retval[size] = ft_strjoin_tab(tab, "=");
	i = 0;
	while (env[i])
	{
		retval[i] = ft_strdup(env[i]);
		i++;
	}
	ft_cleansplits(env);
	return (retval);
}

char		**remove_var(char **env, char *var)
{
	char	**retval;
	size_t	size;
	size_t	i;
	char	*cmp;

	i = 0;
	if (!is_var(env, var))
		return (env);
	size = 0;
	while (env[size])
		size++;
	retval = (char **) malloc(sizeof(char *) * (size));
	retval[size - 1] = 0;
	i = 0;
	cmp = ft_strjoin(var, "=");
	while (i < size - 1)
	{
		if (ft_strstr(env[i], cmp) != env[i])
			retval[i] = ft_strdup(env[i]);
		i++;
	}
	free(cmp);
	ft_cleansplits(env);
	return (retval);
}

char		**update_var(char **env, char *var, char *new_content)
{
	int	i;
	char	*tab[3];
	char	*cmp;

	i = 0;
	cmp = ft_strjoin(var, "=");
	while (env[i] && ft_strstr(env[i], cmp) != env[i])
		i++;
	free(cmp);
	if (!env[i])
		return (0);
	tab[0] = var;
	tab[1] = new_content;
	tab[2] = 0;
	if (env[i])
	{
		free(env[i]);
		env[i] = ft_strjoin_tab(tab, "=");
	}
	else
		return (0);
	if (!env[i])
		return (0);
	return (env);
}

int	is_var(char **env, char *var)
{
	int	i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(var, "=");
	while (env[i] && ft_strstr(env[i], tmp) == 0)
		i++;
	free(tmp);
	if (env[i])
		return (1);
	return (0);
}
