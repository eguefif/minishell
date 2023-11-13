/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:35:07 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/21 17:26:21 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	make_char(t_conv conv, t_string *str)
{
	char	*temp;

	temp = ft_strnew(1);
	if (!temp)
		return ;
	temp[0] = conv.d_char;
	make_replacement(temp, conv, str);
	free(temp);
}
