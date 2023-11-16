/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_env_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:19:49 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/16 15:11:39 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char *str1 = "salut \'$USER fadf a\' $PATH";
	char *str2 = "salut \"$USER fadf a\" $SHELL";
	char *str3 = "salut \"fadf a\" \' \' fsadfdas ";
	char *str4 = "salut \"$USER$USER fadf a\" $USER";
	char *str5 = "salut \"$  fadf a\" $USER";
	char *str6 = "salut \"$  fadf a\" USER$";
	char *str7 = "salut \"$$$  fadf a\" USER$";

	char *user = getenv("USER");
	char *path = getenv("PATH");
	char *shell = getenv("SHELL");

	char *cmp1[] = {path, 0};
	char *cmp2[] = {user, shell, 0};

	char **retval1 = get_env_list(str1);
	if (ft_strcmp(cmp1[0], retval1[0]) != 0)
		ft_printf("Error |%s|\n|%s|\n", retval1[0], cmp1[0]);

	if (retval1[1] !=  0)
		ft_printf("Error\n");

	char **retval2 = get_env_list(str2);
	if (ft_strcmp(cmp2[0], retval2[0]) != 0)
		ft_printf("Error 2\n");

	if (ft_strcmp(cmp2[1], retval2[1]) != 0)
		ft_printf("Error 2\n");

	if (retval2[3] !=  0)
		ft_printf("Error 2\n");

	char **retval3 = get_env_list(str3);
	if (retval3[0] !=  0)
		ft_printf("Error 3\n");

	char **retval4 = get_env_list(str4);
	if (ft_strcmp(user, retval4[0]) != 0)
		ft_printf("Error |%s|\n|%s|\n", retval4[0], user);
	if (ft_strcmp(user, retval4[1]) != 0)
		ft_printf("Error 4\n");
	if (ft_strcmp(user, retval4[2]) != 0)
		ft_printf("Error 4\n");
	if (retval4[3] !=  0)
		ft_printf("Error\n");

	char **retval5 = get_env_list(str5);
	if (ft_strcmp(user, retval5[0]) != 0)
		ft_printf("Error 5\n");
	if (retval5[1] !=  0)
		ft_printf("Error 5\n");

	char **retval6 = get_env_list(str6);
	if (retval6[0] !=  0)
		ft_printf("Error 6\n");

	char **retval7 = get_env_list(str7);
	if (retval7[0] !=  0)
		ft_printf("Error 7\n");
}
