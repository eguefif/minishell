/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:29:53 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/16 09:54:19 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char **result;
	char *check[3];

	result = ms_lexer("echo \" \' $USER machin chose\"truc\" un truc de fou |\"$USERmachin");

	char *user = getenv("USER");
	char *token[] = {" \'", user, " machin chosetruc un truc de fou |", 0};
	check[0] = "echo";
	check[1] = ft_strjoin_tab(token, "");
	check[2] = 0;

	int i = 0;
	while (check[i])
	{
		if (strcmp(result[i], check[i]) != 0)
			printf("Error: | %s | should be | %s |\n", result[i], check[i]);
		i++;
	}
}
