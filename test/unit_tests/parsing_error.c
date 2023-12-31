/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:47:44 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/17 13:11:18 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char ** argv, char **env)
{
	(void) argc;
	(void) argv;
	char	*tab[] = 
	{
		"| cat",
		"echo >>>",
		"echo <<",
		"cat <",
		"cat >",
		">> |",
		"<< |",
		"< |",
		"> |",
		"cat <\"<\" |",
		"cat >> |",
		"cat < <",
		"cat > >",
		"cat ||",
		"cat | |",
		"cat |",
		0
	};
	
	int i = 0;
	while (tab[i])
	{
		if (ms_parser(tab[i], env))
			ft_printf("Error %d\n", i + 1);
		i++;
	}
}
