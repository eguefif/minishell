/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_clean_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:00:18 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/16 09:22:14 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char **result;
	char *check[3];

	result = ms_lexer("ec\"ho\" \'Bonjour \" je m\'\"\'appelle Maxime\"");

	check[0] = "echo";
	check[1] = "Bonjour \" je m\'appelle Maxime";
	check[2] = 0;

	int i = 0;
	while (check[i])
	{
		if (strcmp(result[i], check[i]) != 0)
			printf("Error: | %s | should be | %s |\n", result[i], check[i]);
		i++;
	}
}
