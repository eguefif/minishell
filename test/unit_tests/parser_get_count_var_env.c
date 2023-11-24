/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_count_var_env.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:09:24 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/24 13:27:39 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char *str1 = "salut \'$USER fadf a\' $USER";
	char *str2 = "salut \"$USER fadf a\" $USER";
	char *str3 = "salut \"fadf a\" \' \' fsadfdas ";
	char *str4 = "salut \"$USER$USER fadf a\" $USER";
	char *str5 = "salut \"$  fadf a\" $USER";
	char *str6 = "salut \"$  fadf a\" USER$";
	char *str7 = "salut \"$$$  fadf a\" USER$";
	char *str8 = "$USER$USER$USER'a'$USER";
	char *str9 = "\'\'$HOME";

	int	count;

	count = get_count_var_env(str1);
	if (count != 1)
		ft_printf("Error test 1\n");

	count = get_count_var_env(str2);
	if (count != 2)
		ft_printf("Error test 2\n");

	count = get_count_var_env(str3);
	if (count != 0)
		ft_printf("Error test 3\n");

	count = get_count_var_env(str4);
	if (count != 3)
		ft_printf("Error test 4\n");

	count = get_count_var_env(str5);
	if (count != 1)
		ft_printf("Error test 5\n");

	count = get_count_var_env(str6);
	if (count != 0)
		ft_printf("Error test 6\n");

	count = get_count_var_env(str7);
	if (count != 0)
		ft_printf("Error test 7\n");

	count = get_count_var_env(str8);
	if (count != 4)
		ft_printf("Error test 8\n");

	count = get_count_var_env(str9);
	if (count != 1)
		ft_printf("Error test 9\n");
}
