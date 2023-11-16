/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:00:05 by maxpelle          #+#    #+#             */
/*   Updated: 2023/11/16 10:10:00 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *str1[] = {"ligne1", "ligne2", "ligne3", 0};
	char *str2[] = {0};
	char *str3[] = {"ligne1", 0};
	char *str4[] = {"ligne1", "ligne2", 0};
	
	char *sep1 = "+++";
	char *sep2 = 0;

	char *test1 = ft_strjoin_tab(str1, sep1);
	char *test2 = ft_strjoin_tab(str1, sep2);
	char *test3 = ft_strjoin_tab(str2, sep1);
	char *test4 = ft_strjoin_tab(str2, sep2);
	char *test5 = ft_strjoin_tab(str3, sep1);
	char *test6 = ft_strjoin_tab(str3, sep2);
	char *test7 = ft_strjoin_tab(str4, sep1);
	char *test8 = ft_strjoin_tab(str4, sep2);

	if (ft_strcmp(test1, "ligne1+++ligne2+++ligne3") != 0)
		ft_printf("Error");
	if (ft_strcmp(test2, "ligne1ligne2ligne3") != 0)
		ft_printf("Error");
	if (test3)
		ft_printf("Error");
	if (test4)
		ft_printf("Error");
	if (ft_strcmp(test5, "ligne1") != 0)
		ft_printf("Error");
	if (ft_strcmp(test6, "ligne1") != 0)
		ft_printf("Error");
	if (ft_strcmp(test7, "ligne1+++ligne2") != 0)
		ft_printf("Error");
	if (ft_strcmp(test8, "ligne1ligne2") != 0)
		ft_printf("Error");
}
