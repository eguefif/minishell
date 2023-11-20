/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_getpath.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:40:07 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/20 17:37:48 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command_path(char *command, char **env)
{
	char 	*path;
	char	**paths;
	int		i;
	char	*retval;	
	char	*tab[2];

	if (access(command, F_OK) == 0)
		return (ft_strdup(command));
	path = ms_getenv(env, "PATH");
	if (!path)
		return (0);
	paths = ft_split(path, ':');
	i = 0;
	retval = 0;
	tab[1] = command;
	while (paths[i])
	{
		tab[0] = paths[i];
		retval = ft_strjoin_tab(tab, "/");
		if (access(retval, F_OK) == 0)
			break;
		free(retval);
		retval = 0;
		i++;
	}
	ft_cleansplits(paths);
	return (retval);
}
