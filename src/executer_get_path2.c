/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_get_path2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:43:44 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/25 14:07:17 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_splits(char **env, char *command)
{
	char	*path;
	char	**splits;

	path = ms_getenv(env, "PATH");
	if (!path)
	{
		ft_error_message(command, NO_FILE);
		return (0);
	}
	splits = ft_split(path, ':');
	free(path);
	return (splits);
}
