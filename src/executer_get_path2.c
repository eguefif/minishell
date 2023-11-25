/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_get_path2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:43:44 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/25 12:58:30 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path_splits(char **env, char *command)
{
	char	*path;

	path = ms_getenv(env, "PATH");
	if (!path)
	{
		ft_error_message(command, NO_FILE);
		return (0);
	}
	free(path);
	return (ft_split(path, ':'));
}
