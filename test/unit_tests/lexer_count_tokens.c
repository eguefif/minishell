/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_count_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:03:39 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/17 10:37:29 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *tab[] = {
		"ec\"ho\" \'Bonjour \" je m\'\"\'appelle Maxime\"",
		"echo<file1>>file2||<<file3 test",
		"echo \'salut \"je suis\" un test\'",
		"echo \"salut \'je suis\' u ntest\"",
		"echo \"salut \' je sui\"",
		"echo \'salut \"je suis\'",
		"echo test test \'salut \"je suis\'",
		"cat requirements.txt >test2<test1>test2"
	};

	int tab_check[] = {
		2,
		10,
		2,
		2,
		2,
		2,
		4,
		8
	};
	int i = 0;
	while (i < 8)
	{
		char *line = ft_strdup(tab[i]);
		int size = count_tokens(line);
		if (size != tab_check[i])
			ft_printf("Error on string %i:%i should be %i\n",
					i + 1, size, tab_check[i]);
		i++;
	}
}
