/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_clean_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:42:18 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/13 18:24:55 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *tab[] = {
		"abc\"def",
		"abc\"d\"ef",
		"ab\"c\'\"ef",
		"\'abc\'", 
		"\'abc",
		"abc\'",
		"ab\"def\'ghi\'klm",
		"ab\"def\'ghi\'klm\"a",
		"\'",
		"\"",
		"\"salut\"bonjour\'salut\'\'hello\'\"bonjour\'\'",
		"echo test test \'salut \"je suis\'"

	};

	char *tab_check[] = {
		"abcdef",
		"abc\"d\"ef",
		"ab\"c\'\"ef",
		"\'abc\'", 
		"abc",
		"abc",
		"abdef\'ghi\'klm",
		"ab\"def\'ghi\'klm\"a",
		"",
		"",
		"\"salut\"bonjour\'salut\'\'hello\'bonjour\'\'",
		"echo test test \'salut \"je suis\'"
	};
	int i = 0;
	while (i < 11)
	{
		char *line = ft_strdup(tab[i]);
		ft_printf("Before: %s\n", line);
		line = clean_line(line);
		ft_printf("After: %s\n", line);
		if (ft_strcmp(line, tab_check[i]) != 0)
			ft_printf("Error on string %i:\n\t%s\n\t%s\n",
					i, line, tab_check[i]);
		i++;
	}
}
