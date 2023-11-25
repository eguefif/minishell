/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_getpath.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:40:07 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/25 12:14:13 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_relative_path(char *command);
static int	is_abs_path(char *command);
static void	handle_error(char *command);
static char	*check_paths(char *paths, char *command);

char	*get_command_path(char *command, char **env)
{
	char	*path;
	char	**paths;
	int		i;
	char	*retval;	

	if (is_relative_path(command) || is_abs_path(command))
		if (access(command, F_OK) == 0)
			return (ft_strdup(command));
	path = ms_getenv(env, "PATH");
	if (!path)
		return (0);
	paths = ft_split(path, ':');
	i = -1;
	while (paths[++i])
	{
		retval = check_paths(paths[i], command);
		if (retval)
			break ;
	}
	ft_cleansplits(paths);
	if (retval == 0)
		handle_error(command);
	free(path);
	return (retval);
}

static int	is_relative_path(char *command)
{
	if (command[0] == '.' && command[1] == '/')
		return (1);
	return (0);
}

static int	is_abs_path(char *command)
{
	if (command[0] == '/')
		return (1);
	return (0);
}

static void	handle_error(char *command)
{
	if (command[0] && command[0] == '.')
		ft_error_message(command, NO_FILE);
	else
		ft_error_message(command, COMMAND_NOT_FOUND);
}

static char	*check_paths(char *path, char *command)
{
	char	*retval;
	char	*tab[3];

	tab[1] = command;
	tab[2] = 0;
	retval = 0;
	tab[0] = path;
	retval = ft_strjoin_tab(tab, "/");
	if (access(retval, F_OK) == 0)
		return (retval);
	free(retval);
	retval = 0;
	return (0);
}
