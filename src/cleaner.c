/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:16:08 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/15 17:14:32 by eguefif          ###   ########.fr       */
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

void	ms_clean_commands(t_command *commands)
{
	int		i;
	int		j;

	i = 0;
	if (!commands)
		return ;
	while (!commands[i].last)
	{
		j = 0;
		if (commands[i].args)
		{
			while (commands[i].args[j])
			{
				free(commands[i].args[j]);
				j++;
			}
			free(commands[i].args);
		}
		if (commands[i].redirections.r_stdin)
			free(commands[i].redirections.r_stdin);
		if (commands[i].redirections.r_stdout)
			free(commands[i].redirections.r_stdout);
		i++;
	}
	free(commands);
}
