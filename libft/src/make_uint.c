/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_uint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:04:32 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/24 10:04:17 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	make_uint(t_conv conv, t_string *str)
{
	char	*nbr;

	nbr = 0;
	if (conv.specifier == 'x')
		nbr = ft_lutoa_base(conv.d_unbr, "0123456789abcdef");
	else if (conv.specifier == 'X')
		nbr = ft_lutoa_base(conv.d_unbr, "0123456789ABCDEF");
	else if (conv.specifier == 'u')
		nbr = ft_lutoa_base(conv.d_unbr, "0123456789");
	nbr = make_precision(nbr, conv);
	make_replacement(nbr, conv, str);
	free(nbr);
}
