/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:35:02 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/24 12:51:14 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *tab[] = {
		"ec\"ho\" \'Bonjour \" je m\'\"\'appelle Maxime\"",
		"echo \'salut \"je suis\" un test\'",
		"echo \"salut \'je suis\' u ntest\"",
		"echo test test \'salut \"je suis\'",
		"< file.txt cat -e | tail > output.txt",
		"cat -e",
		"<file.txt cat>file.txt",
		"<file.txt cat>file.txt|tail>output.x",
		"ls -ls",
		"/bin/ls",
		"/bin/ls\t\t\t\t      |        tail > output.txt -c 8",
		"",
		"cat requirements.txt >test2<test1>test2",
		"cat ||",
		"cat | | ",
		"cat <\"<\"",
		"echo $USER$USER$USER\'a\'$USER",
		"echo \"\'\"h\'h\'la\"\'\"",
		"echo \'\'$HOME",
		"\"e\"\'c\'ho \'b\'\"o\"nj\"o\"\'u\'r"
	};
	char	*cmp17[] = {
		"echo", "$USER$USER$USER\'a\'$USER"
	};
	char	*cmp18[] = {
		"echo", "\"\'\"h\'h\'la\"\'\""
	};
	char	*cmp19[] = {
		"echo", "\'\'$HOME"
	};
	char	*cmp20[] = {
		"\"e\"\'c\'ho", "\'b\'\"o\"nj\"o\"\'u\'r"
	};
	char	*cmp1[] = {
		"ec\"ho\"", "\'Bonjour \" je m\'\"\'appelle Maxime\""
	};
	char	*cmp2[] = {
		"echo", "\'salut \"je suis\" un test\'"
	};
	char	*cmp3[] = {
		"echo", "\"salut \'je suis\' u ntest\""
	};
	char	*cmp4[] = {
		"echo", "test",  "test", "\'salut \"je suis\'"};
	char	*cmp5[] = {
		"<", "file.txt", "cat", "-e", "|", "tail", ">", "output.txt"
	};
	char	*cmp6[] = {
		"cat", "-e"
	};
	char	*cmp7[] = {
		"<", "file.txt", "cat", ">", "file.txt"
	};
	char	*cmp8[] = {
		"<", "file.txt", "cat", ">", "file.txt", "|", "tail", ">", "output.x"
	};
	char	*cmp9[] = {
		"ls",  "-ls"
	};
	char	*cmp10[] = {
		"/bin/ls"
	};
	char	*cmp11[] = {
		"/bin/ls", "|", "tail", ">", "output.txt", "-c", "8"
	};
	char	*cmp12[] = {
		""
	};
	char	*cmp13[] = {
		"cat", "requirements.txt", ">", "test2", "<", "test1", ">", "test2"
	};
	char	*cmp14[] = {
		"cat", "|", "|"
	};
	char	*cmp15[] = {
		"cat", "|", "|"
	};
	char	*cmp16[] = {
		"cat", "<", "\"<\""
	};

	char	**cmp[] = {cmp1, cmp2, cmp3, cmp4, cmp5, cmp6, cmp7, cmp8, cmp9, cmp10, cmp11, cmp12, cmp13, cmp14, cmp15, cmp16, cmp17, cmp18, cmp19, cmp20};
	char	**retval;
	int		i = 0;
	int		j;
	size_t	size;
	
	// Test1
	while (i < 20)
	{
		size = count_tokens(tab[i]);
		retval = get_tokens(tab[i], size);
		j = 0;
		while (retval[j])
		{
			if (ft_strcmp(retval[j], cmp[i][j]) != 0)
				ft_printf("Error on test %d:\n\t|%s|\n\t|%s|\n", i, retval[j], cmp[i][j]);	
			j++;
		}
		ft_cleansplits(retval);
		i++;
	}	
}
