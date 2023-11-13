/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:10:46 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/13 14:47:40 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_parser(char *line)
{
	char	**arg;

	line = ft_strtrim(line, "\n \t");
	arg = 0;
	arg = ft_split(line, ' ');
	free(line);
	return (arg);		
}
