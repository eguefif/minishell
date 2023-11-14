/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:08 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/14 15:46:36 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cleanup(char **commands)
{
	ft_cleansplits(commands);
}

void	ms_clean_tokens(char **tokens)
{
	int	j;

	j = 0;
	if (tokens)
	{
		while (tokens[j])
		{
			if (tokens[j])
				free(tokens[j]);
			j++;
		}
		free(tokens);
	}
}
