/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_env_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:19:49 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/24 13:27:40 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	char *str1 = "salut \'$USER fadf a\' $PATH";
	char *str2 = "salut \"$USER fadf a\" $SHELL";
	char *str3 = "salut \"fadf a\" \' \' fsadfdas ";
	char *str4 = "salut \"$USER$USER fadf a\" $USER";
	char *str5 = "salut \"$  fadf a\" $USER";
	char *str6 = "salut \"$  fadf a\" USER$";
	char *str7 = "salut \"$$$  fadf a\" USER$";
	char *str8 = "$USER$USER$USER'a'$USER";
	char *str9 = "\'\'$HOME";

	char *user = getenv("USER");
	char *path = getenv("PATH");
	char *shell = getenv("SHELL");
	char *home = getenv("HOME");

	char *cmp1[] = {path, 0};
	char *cmp2[] = {user, shell, 0};

	char **retval1 = get_env_list(str1, env);
	if (ft_strcmp(cmp1[0], retval1[0]) != 0)
		ft_printf("Error |%s|\n|%s|\n", retval1[0], cmp1[0]);

	if (retval1[1] !=  0)
		ft_printf("Error\n");

	char **retval2 = get_env_list(str2, env);
	if (ft_strcmp(cmp2[0], retval2[0]) != 0)
		ft_printf("Error 2: %s should be %s\n", retval2[0], cmp2[0]);

	if (ft_strcmp(cmp2[1], retval2[1]) != 0)
		ft_printf("Error 2.1\n");

	if (retval2[2] !=  0)
		ft_printf("Error 2.2\n");

	char **retval3 = get_env_list(str3, env);
	if (retval3[0] !=  0)
		ft_printf("Error 3\n");

	char **retval4 = get_env_list(str4, env);
	if (ft_strcmp(user, retval4[0]) != 0)
		ft_printf("Error |%s|\n|%s|\n", retval4[0], user);
	if (ft_strcmp(user, retval4[1]) != 0)
		ft_printf("Error 4\n");
	if (ft_strcmp(user, retval4[2]) != 0)
		ft_printf("Error 4\n");
	if (retval4[3] !=  0)
		ft_printf("Error\n");

	char **retval5 = get_env_list(str5, env);
	if (ft_strcmp(user, retval5[0]) != 0)
		ft_printf("Error 5\n");
	if (retval5[1] !=  0)
		ft_printf("Error 5\n");

	char **retval6 = get_env_list(str6, env);
	if (retval6[0] !=  0)
		ft_printf("Error 6\n");

	char **retval7 = get_env_list(str7, env);
	if (retval7[0] !=  0)
		ft_printf("Error 7\n");

	char **retval8 = get_env_list(str8, env);
	if (ft_strcmp(user, retval8[0]) != 0)
		ft_printf("Error 8.1\n");
	if (ft_strcmp(user, retval8[1]) != 0)
		ft_printf("Error 8.2\n");
	if (ft_strcmp(user, retval8[2]) != 0)
		ft_printf("Error 8.3\n");
	if (ft_strcmp(user, retval8[3]) != 0)
		ft_printf("Error 8.4\n");
	if (retval5[4] !=  0)
		ft_printf("Error 8.5\n");

	char **retval9 = get_env_list(str9, env);
	if (ft_strcmp(home, retval9[0]) != 0)
		ft_printf("Error 9\n");
	if (retval9[1] != 0)
		ft_printf("Error 9.2\n");
}
