/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:22:47 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/16 09:28:09 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char **result;
	char *check[3];

	result = ms_lexer("echo $USER\"True\"");

	char *user = getenv("USER");
	check[0] = "echo";
	check[1] = ft_strjoin(user, "True");
	check[2] = 0;

	int i = 0;
	while (check[i])
	{
		if (strcmp(result[i], check[i]) != 0)
			printf("Error: | %s | should be | %s |\n", result[i], check[i]);
		i++;
	}
}
