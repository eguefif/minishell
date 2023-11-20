/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:12:18 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/20 17:27:02 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_command *commands)
{
	ms_clean_commands(commands);
	exit(1);
}

void	ft_exit_nb(t_command *commands, int retval)
{
	ms_clean_commands(commands);
	exit(retval);
}

int	is_dir(char *path)
{
	struct stat st;

	if (stat(path, &st) == -1)
		return (-1);
	return (st.st_mode & S_IFDIR);
}
