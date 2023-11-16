/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_new_token_size.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:55 by eguefif           #+#    #+#             */
/*   Updated: 2023/11/16 16:22:43 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char *str1 = "salut \'$USER fadf a\' $USER";
	int	count;
	char *user = getenv("USER");
	int	size;
	
	char *str8 = "\'\'\"\"$$$$$$";
	size = ft_strlen("$$$$$$");
	char *list8[] = {0};
	count = get_new_token_size(str8, list8);
	if (count != size)
		ft_printf("Error test 8: %d should be %d\n", count, size);

	char *str7 = "";
	size = ft_strlen("");
	char *list7[] = {0};
	count = get_new_token_size(str7, list7);
	if (count != size)
		ft_printf("Error test 7: %d should be %d\n", count, size);

	char *str6 = "$USER";
	size = ft_strlen(user);
	char *list6[] = {user, 0};
	count = get_new_token_size(str6, list6);
	if (count != size)
		ft_printf("Error test 6: %d should be %d\n", count, size);

	char *str5 = "$user";
	size = ft_strlen("");
	char *list5[] = {0};
	count = get_new_token_size(str5, list5);
	if (count != size)
		ft_printf("Error test 5: %d should be %d\n", count, size);

	char *str4 = "salut je suis un test \'sans \"rien \'";
	size = ft_strlen("salut je suis un test sans \"rien ");
	char *list4[] = {0};
	count = get_new_token_size(str4, list4);
	if (count != size)
		ft_printf("Error test 4: %d should be %d\n", count, size);

	char *str3 = "salut je suis \"un\'  \"test \'sans \"rien \'";
	size = ft_strlen("salut je suis un\'  test sans \"rien ");
	char *list3[] = {0};
	count = get_new_token_size(str3, list3);
	if (count != size)
		ft_printf("Error test 3: %d should be %d\n", count, size);

	char *str2 = "$salut $ \'$USER fadf a\' $$$USER";
	size = ft_strlen(user) + ft_strlen(" $ $USER fadf a $$");
	char *list2[] = {user, 0};
	count = get_new_token_size(str2, list2);
	if (count != size)
		ft_printf("Error test 1: %d should be %d\n", count, size);

	size = ft_strlen(user) + ft_strlen("salut $USER fadf a ");
	char *list[] = {user, 0};
	count = get_new_token_size(str1, list);
	if (count != size)
		ft_printf("Error test 2: %d should be %d\n", count, size);

}
