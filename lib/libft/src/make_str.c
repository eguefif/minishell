/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:14:33 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/21 17:26:38 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	make_str(t_conv conv, t_string *str)
{
	if (conv.d_str)
		make_replacement(conv.d_str, conv, str);
	else
	{
		conv.d_str = "(null)";
		make_replacement("(null)", conv, str);
	}
}
