/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:12:18 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/25 15:17:44 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_command *commands)
{
	ms_clean_commands(commands);
	exit(1);
}

void	ft_exit_nb(t_command *commands, int retval, char **env)
{
	ms_clean_commands(commands);
	ft_cleansplits(env);
	exit(retval);
}

int	is_dir(char *path)
{
	struct stat	st;

	if (!path)
		return (0);
	if (stat(path, &st) == -1)
		return (-1);
	return (st.st_mode & S_IFDIR);
}

int	is_file(char *path)
{
	struct stat	st;

	if (!path)
		return (0);
	if (stat(path, &st) == -1)
		return (-1);
	return (st.st_mode & S_IFREG);
}
