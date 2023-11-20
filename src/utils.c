/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:12:18 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/20 10:15:32 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_command *commands)
{
	ft_dprintf(2, "error\n");
	ms_clean_commands(commands);
	exit(1);
}
