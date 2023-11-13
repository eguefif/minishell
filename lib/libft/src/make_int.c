/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:00:03 by eguefif           #+#    #+#             */
/*   Updated: 2023/10/24 10:04:17 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	make_int(t_conv conv, t_string *str)
{
	char		*nbr;

	nbr = ft_itoa(conv.d_nbr);
	nbr = make_precision(nbr, conv);
	make_replacement(nbr, conv, str);
	free(nbr);
}
