/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_count_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:03:39 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/14 14:55:09 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *tab[] = {
		"echo \'salut \"je suis\" un test\'",
		"echo \"salut \'je suis\' u ntest\"",
		"echo \"salut \' je sui\"",
		"echo \'salut \"je suis\'",
		"echo test test \'salut \"je suis\'"
	};

	int tab_check[] = {
		2,
		2,
		2,
		2,
		4
	};
	int i = 0;
	while (i < 5)
	{
		char *line = ft_strdup(tab[i]);
		int size = count_tokens(line);
		if (size != tab_check[i])
			ft_printf("Error on string %i:%i should be %i\n",
					i + 1, size, tab_check[i]);
		i++;
	}
}
